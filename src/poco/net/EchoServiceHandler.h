//
// Created by JackyWoo on 2022/4/18.
//

#pragma once

#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketAcceptor.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/NObserver.h>
#include <Poco/Exception.h>
#include <Poco/Thread.h>
#include <Poco/FIFOBuffer.h>
#include <Poco/Delegate.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/ThreadPool.h>

using namespace Poco;
using namespace Poco::Net;

class EchoServiceHandler
    /// I/O handler class. This class (un)registers handlers for I/O based on
    /// data availability. To ensure non-blocking behavior and alleviate spurious
    /// socket writability callback triggering when no data to be sent is available,
    /// FIFO buffers are used. I/O FIFOBuffer sends notifications on transitions
    /// from [1] non-readable (i.e. empty) to readable, [2] writable to non-writable
    /// (i.e. full) and [3] non-writable (i.e. full) to writable.
    /// Based on these notifications, the handler member functions react by
    /// enabling/disabling respective reactor framework notifications.
{
public:
    EchoServiceHandler(StreamSocket& socket, SocketReactor& reactor):
            _socket(socket),
            _reactor(reactor),
            _fifoIn(BUFFER_SIZE, true),
            _fifoOut(BUFFER_SIZE, true)
    {
        logger->information("Connection from " + socket.peerAddress().toString());

        _reactor.addEventHandler(_socket, NObserver<EchoServiceHandler, ReadableNotification>(*this, &EchoServiceHandler::onSocketReadable));
        _reactor.addEventHandler(_socket, NObserver<EchoServiceHandler, ShutdownNotification>(*this, &EchoServiceHandler::onSocketShutdown));

        _fifoOut.readable += delegate(this, &EchoServiceHandler::onFIFOOutReadable);
        _fifoIn.writable += delegate(this, &EchoServiceHandler::onFIFOInWritable);
    }

    ~EchoServiceHandler()
    {
        try
        {
            logger->information("Disconnecting " + _socket.peerAddress().toString());
        }
        catch (...)
        {
        }
        _reactor.removeEventHandler(_socket, NObserver<EchoServiceHandler, ReadableNotification>(*this, &EchoServiceHandler::onSocketReadable));
        _reactor.removeEventHandler(_socket, NObserver<EchoServiceHandler, WritableNotification>(*this, &EchoServiceHandler::onSocketWritable));
        _reactor.removeEventHandler(_socket, NObserver<EchoServiceHandler, ShutdownNotification>(*this, &EchoServiceHandler::onSocketShutdown));

        _fifoOut.readable -= delegate(this, &EchoServiceHandler::onFIFOOutReadable);
        _fifoIn.writable -= delegate(this, &EchoServiceHandler::onFIFOInWritable);
    }

    void onFIFOOutReadable(bool& b)
    {
        if (b)
        {
            logger->information(format("add socket %s writable event", _socket.peerAddress().toString()));
            _reactor.addEventHandler(
                _socket, NObserver<EchoServiceHandler, WritableNotification>(*this, &EchoServiceHandler::onSocketWritable));
        }
        else
        {
            logger->information(format("remove socket %s writable event", _socket.peerAddress().toString()));
            _reactor.removeEventHandler(
                _socket, NObserver<EchoServiceHandler, WritableNotification>(*this, &EchoServiceHandler::onSocketWritable));
        }
    }

    void onFIFOInWritable(bool& b)
    {
        if (b)
        {
            logger->information(format("add socket %s readable event", _socket.peerAddress().toString()));
            _reactor.addEventHandler(
                _socket, NObserver<EchoServiceHandler, ReadableNotification>(*this, &EchoServiceHandler::onSocketReadable));
        }
        else
        {
            logger->information(format("remove socket %s readable event", _socket.peerAddress().toString()));
            _reactor.removeEventHandler(
                _socket, NObserver<EchoServiceHandler, ReadableNotification>(*this, &EchoServiceHandler::onSocketReadable));
        }
    }

    void onSocketReadable(const AutoPtr<ReadableNotification>& pNf)
    {
        logger->information(format("socket %s is readable", _socket.peerAddress().toString()));
        try
        {
            int len = _socket.receiveBytes(_fifoIn);
            logger->information("Socket readable event " +pNf->name()+ ", receive bytes " + std::to_string(len));
            if (len > 0)
            {
                size_t size  = _fifoOut.write(_fifoIn.buffer(), _fifoIn.used());
                logger->information("Socket write data length " + std::to_string(len));
                if (size)
                    _fifoIn.drain();
            }
            else
            {
                logger->information(format("Socket %s readable but receive nothing, close it!", _socket.peerAddress().toString()));
                delete this;
            }
        }
        catch (Poco::Exception& exc)
        {
            logger->error(exc.message());
            delete this;
        }
    }

    void onSocketWritable(const AutoPtr<WritableNotification>& pNf)
    {
        try
        {
            logger->information(format("socket %s is writable", _socket.peerAddress().toString()));
            _socket.sendBytes(_fifoOut);
        }
        catch (Poco::Exception& exc)
        {
            logger->error(exc.message());
            delete this;
        }
    }

    void onSocketShutdown(const AutoPtr<ShutdownNotification>& pNf)
    {
        logger->information(format("socket %s shutdown", _socket.peerAddress().toString()));
        delete this;
    }

private:
    enum
    {
        BUFFER_SIZE = 1024
    };

    Logger * logger = &Logger::get("EchoServiceHandler");

    StreamSocket   _socket;
    SocketReactor& _reactor;
    FIFOBuffer     _fifoIn;
    FIFOBuffer     _fifoOut;
};

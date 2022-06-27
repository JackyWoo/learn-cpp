//
// EchoServer.cpp
//
// This sample demonstrates the SocketReactor and SocketAcceptor classes.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketAcceptor.h>
#include <Poco/Net/ParallelSocketReactor.h>
#include <Poco/Net/ParallelSocketAcceptor.h>
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
#include <iostream>

#include "EchoServiceHandler.h"


using Poco::Net::SocketReactor;
using Poco::Net::SocketAcceptor;
using Poco::Net::ReadableNotification;
using Poco::Net::WritableNotification;
using Poco::Net::ShutdownNotification;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::NObserver;
using Poco::AutoPtr;
using Poco::Thread;
using Poco::FIFOBuffer;
using Poco::delegate;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;



class EchoServer: public Poco::Util::ServerApplication
    /// The main application class.
    ///
    /// This class handles command-line arguments and
    /// configuration files.
    /// Start the EchoServer executable with the help
    /// option (/help on Windows, --help on Unix) for
    /// the available command line options.
    ///
    /// To use the sample configuration file (EchoServer.properties),
    /// copy the file to the directory where the EchoServer executable
    /// resides. If you start the debug version of the EchoServer
    /// (EchoServerd[.exe]), you must also create a copy of the configuration
    /// file named EchoServerd.properties. In the configuration file, you
    /// can specify the port on which the server is listening (default
    /// 9977) and the format of the date/time string sent back to the client.
    ///
    /// To test the EchoServer you can use any telnet client (telnet localhost 9977).
{
public:
    EchoServer(): _helpRequested(false)
    {
    }

    ~EchoServer()
    {
    }

protected:
    void initialize(Application& self)
    {
        loadConfiguration(); // load default configuration files, if present
        ServerApplication::initialize(self);
    }

    void uninitialize()
    {
        ServerApplication::uninitialize();
    }

    void defineOptions(OptionSet& options)
    {
        ServerApplication::defineOptions(options);

        options.addOption(
                Option("help", "h", "display help information on command line arguments")
                        .required(false)
                        .repeatable(false));
    }

    void handleOption(const std::string& name, const std::string& value)
    {
        ServerApplication::handleOption(name, value);

        if (name == "help")
            _helpRequested = true;
    }

    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("An echo server implemented using the Reactor and Acceptor patterns.");
        helpFormatter.format(std::cout);
    }

    int main(const std::vector<std::string>& args)
    {
        if (_helpRequested)
        {
            displayHelp();
        }
        else
        {
            // get parameters from configuration file
            unsigned short port = (unsigned short) config().getInt("EchoServer.port", 9977);

            // set-up a server socket
            ServerSocket svs(port);
            svs.setBlocking(false);
            // set-up a SocketReactor...
            ParallelSocketReactor<SocketReactor> reactor;
            // ... and a SocketAcceptor
            ParallelSocketAcceptor<EchoServiceHandler, SocketReactor> acceptor(svs, reactor, 1);
            // run the reactor in its own thread so that we can wait for
            // a termination request
//            Thread thread;
//            thread.start(reactor);
            // wait for CTRL-C or kill
            waitForTerminationRequest();
            Thread::sleep(10000000);
            // Stop the SocketReactor
            reactor.stop();
//            thread.join();
        }
        return Application::EXIT_OK;
    }

private:
    bool _helpRequested;
};


int main(int argc, char** argv)
{
    EchoServer app;
    return app.run(argc, argv);
}

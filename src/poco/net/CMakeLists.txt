add_executable(EchoServer EchoServer.cpp EchoServiceHandler.h)

target_link_libraries (EchoServer
        PUBLIC
        Poco::Net
        Poco::Net::SSL
        Poco::Util
        Poco::Foundation
        #        replxx
        #        cctz
        #        fmt
        )
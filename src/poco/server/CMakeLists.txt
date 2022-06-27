add_executable(DemoServer DemoServer.cpp)

target_link_libraries (DemoServer
        PUBLIC
        Poco::Util
        Poco::Foundation
)
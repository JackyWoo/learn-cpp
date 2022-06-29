add_subdirectory(net)
add_subdirectory(server)

add_executable(PocoTest PocoTest.cpp)

target_link_libraries(PocoTest PUBLIC Poco::Foundation)
add_library(StackTrace stack_trace/StackTrace.cpp)
add_executable(StackTraceTest stack_trace/StackTraceTest.cpp)

target_link_libraries(StackTraceTest StackTrace)

add_executable(QueueTest QueueTest.cpp)
target_link_libraries(QueueTest concurrentqueue)

add_executable(ExtensionDemo ExtensionDemo.cpp)

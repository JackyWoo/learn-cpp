#--------------  ThreadPoolTest --------------

#add_executable(GroupedThreadPool threadpool/GroupedThreadPool.cpp threadpool/getNumberOfPhysicalCPUCores.cpp)
add_library(utils
        threadpool/GroupedThreadPool.cpp
        buffer/ByteBuffer.cpp
        Stopwatch.h
        )

target_include_directories(utils
        PUBLIC SYSTEM
        threadpool/GroupedThreadPool.h
        buffer/ByteBuffer.h
        ObjectCreator.h
        )

add_executable(GroupedThreadPoolTest threadpool/GroupedThreadPoolTest.cpp)
target_link_libraries(GroupedThreadPoolTest utils)

add_executable(ByteBufferTest buffer/ByteBufferTest.cpp)
target_link_libraries(ByteBufferTest utils)

add_executable(ObjectCreatorTest ObjectCreatorTest.cpp)
target_link_libraries(ObjectCreatorTest utils)

add_executable(LevenshteinDistanceTest LevenshteinDistanceTest.cpp)
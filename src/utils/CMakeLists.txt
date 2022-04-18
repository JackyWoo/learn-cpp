#--------------  ThreadPoolTest --------------

#add_executable(GroupedThreadPool threadpool/GroupedThreadPool.cpp threadpool/getNumberOfPhysicalCPUCores.cpp)
add_library(utils threadpool/GroupedThreadPoolTest.cpp threadpool/GroupedThreadPool.cpp)
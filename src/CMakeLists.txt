

#--------------  ThreadPoolTest --------------

#add_executable(GroupedThreadPool threadpool/GroupedThreadPool.cpp threadpool/getNumberOfPhysicalCPUCores.cpp)
add_library(GroupedThreadPoolTest src/utils/threadpool/GroupedThreadPoolTest.cpp src/utils/threadpool/GroupedThreadPool.cpp)
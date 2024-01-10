#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")

add_executable(Thread_deadlock Thread_deadlock.cpp)
add_executable(Thread_head_use_after_free Thread_head_use_after_free.cpp)
add_executable(Thread_race Thread_race.cpp)
add_executable(Thread_race_atomic Thread_race_atomic.cpp)
add_executable(Thread_thread_leak Thread_thread_leak.cpp)

#target_link_libraries(Thread_race -fsanitize=thread)


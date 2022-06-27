cmake_minimum_required(VERSION 3.16)

project(LEARN_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG )
set(CMAKE_CXX_FLAGS -pthread)



add_executable(test Test.cpp)
add_executable(test2 Test2.cpp)

target_compile_options(test
        PRIVATE
        -Wno-user-defined-warnings
        -Wno-writable-strings
 )

#------------------------------------- macros -------------------------

macro(add_headers_and_sources prefix common_path)
#    add_glob(${prefix}_headers ${CMAKE_CURRENT_SOURCE_DIR} ${common_path}/*.h)
    file(GLOB ${prefix}_sources ${common_path}/*.cpp ${common_path}/*.c ${common_path}/*.h)
endmacro()

add_subdirectory(src)

#----------------------------------------- global option -----------------------------

message(STATUS "CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (COMPILER_GCC 1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    set (COMPILER_CLANG 1) # Safe to treat AppleClang as a regular Clang, in general.
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set (COMPILER_CLANG 1)
endif ()
message(STATUS "COMPILER_CLANG = ${COMPILER_CLANG}" )

message(STATUS "LEARN_CPP_SOURCE_DIR = ${LEARN_CPP_SOURCE_DIR}" )
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}" )

set (USE_INTERNAL_POCO_LIBRARY 1)
message(STATUS "USE_INTERNAL_POCO_LIBRARY = ${USE_INTERNAL_POCO_LIBRARY}" )

#----------------------------------------- poco option -----------------------------
set (USE_EPOLL 0)
message(STATUS "USE_EPOLL = ${USE_EPOLL}" )
set (ENABLE_SSL 1)
message(STATUS "ENABLE_SSL = ${ENABLE_SSL}" )

add_subdirectory(contrib)


#------------------------------------- cmake demo -------------------------
add_subdirectory(cmake-demo)


add_subdirectory(openssl-demp)


cmake_minimum_required(VERSION 3.16)

project(LEARN_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG )
set(CMAKE_CXX_FLAGS -pthread)

add_executable(test Test.cpp)

#------------------------------------- basic -------------------------

add_subdirectory(src)

#----------------------------------------- poco -----------------------------

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

set (ENABLE_SSL 0)
message(STATUS "ENABLE_SSL = ${ENABLE_SSL}" )

set (USE_INTERNAL_POCO_LIBRARY 1)
message(STATUS "USE_INTERNAL_POCO_LIBRARY = ${USE_INTERNAL_POCO_LIBRARY}" )

add_subdirectory(contrib)



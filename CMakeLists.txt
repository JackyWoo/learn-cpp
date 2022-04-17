cmake_minimum_required(VERSION 3.16)

project(LEARN_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG )
set(CMAKE_CXX_FLAGS -pthread)



add_executable(test Test.cpp)


#------------------------------------- basic -------------------------

add_subdirectory(src)

# --------------  type --------------
add_executable(TypeTest src/basic/type/TypeTest.cpp )
add_executable(structTest src/basic/type/StructTest.cpp src/basic/type/Person.h src/basic/type/Uu.cpp src/basic/type/Color.h)
add_executable(pointerTest src/basic/type/Pointer.cpp)
add_executable(ArrayTest src/basic/type/ArrayTest.cpp src/basic/clib/CCTypeTest.cpp)
add_executable(ReferenceTest src/basic/type/ReferenceTest.cpp)
add_executable(StringTest src/basic/type/StringTest.cpp)

add_executable(MemCommitTest src/basic/sys/MemCommitTest.cpp)
add_executable(ThreadScheduleTest src/basic/sys/ThreadScheduleTest.cpp)

add_executable(FunctionTest src/basic/sys/FunctionTest.cpp)

add_executable(Jill src/basic/namespace/Jill.cpp)
add_executable(externTest src/basic/type/extern/Main.cpp src/basic/type/extern/Support.cpp)

# --------------  constructor --------------

add_executable(NewTest src/basic/operator/NewTest.cpp)


# --------------  oop --------------

add_executable(Stock src/basic/oop/Stock.h src/basic/oop/Stock.cpp src/basic/oop/Invoker.cpp src/basic/oop/OpStock.cpp)
add_executable(MethodOverrideTest src/basic/oop/MethodOverrideTest.cpp )
add_executable(PolyTest src/basic/oop/PolyTest.cpp )
add_executable(PeopleTest src/basic/oop/PeopleTest.cpp src/basic/oop/People.cpp src/basic/oop/Man.cpp)


# --------------  STL --------------

add_executable(StringTest1 src/basic/stl/StringTest.cpp)
add_executable(VectorTest src/basic/stl/VectorTest.cpp)
add_executable(MapTest src/basic/stl/MapTest.cpp)
add_executable(MapBenchmark src/basic/stl/MapBenchmark.cpp)
add_executable(ListTest src/basic/stl/ListTest.cpp)
add_executable(SetTest src/basic/stl/SetTest.cpp)


# --------------  Template --------------



#--------------  queue --------------

add_executable(BlockingQueueTest src/basic/queue/BlockingQueueTest.cpp)
add_executable(ThreadPoolTest src/basic/queue/FixedThreadPool.cpp src/basic/queue/FixedThreadPoolTest.cpp)

#--------------  x_ptr --------------

add_executable(ResourceReleaseTest src/basic/x_ptr/ResourceReleaseTest.cpp  src/basic/oop/Stock.h  src/basic/oop/Stock.cpp)
add_executable(SegFaultTest src/basic/x_ptr/SegFaultTest.cpp )


add_executable(UniquePtrTest src/basic/x_ptr/UniquePtrTest.cpp)
add_executable(SharedPtrTest src/basic/x_ptr/SharedPtrTest.cpp)
add_executable(NullPtrTest src/basic/x_ptr/NullPtrTest.cpp)

#--------------  pointer --------------



#--------------  ref --------------

add_executable(RefTest src/basic/ref/RefTest.cpp)
add_executable(RefTest2 src/basic/ref/RefTest2.cpp)

#--------------  thread --------------

add_executable(ThreadTest src/basic/thread/ThreadTest.cpp)

#--------------  cpp11 --------------

add_executable(BackReturnTypeTest src/basic/cpp11/BackReturnTypeTest.cpp)
add_executable(DefaultTemplateArgName src/basic/cpp11/DefaultTemplateArgName.cpp)
add_executable(InitObjectTest src/basic/cpp11/InitObjectTest.cpp)
add_executable(MoveConstructorTest src/basic/cpp11/MoveConstructorTest.cpp)
add_executable(MoveConstructorTest2 src/basic/cpp11/MoveConstructorTest2.cpp)
add_executable(MoveConstructorTest3 src/basic/cpp11/MoveConstructorTest3.cpp)
add_executable(ArgDeliverTest src/basic/cpp11/PerfectForwarding.cpp)
add_executable(ConstexprTest src/basic/cpp11/ConstexprTest.cpp)


#--------------  operator --------------

add_executable(OperatorOverrideTest src/basic/operator/OperatorOverrideTest.cpp)
add_executable(OperatorOverrideTest1 src/basic/operator/OperatorOverrideTest1.cpp)

#--------------  template --------------

add_executable(ArrayTemplateTest src/basic/template/ArrayTemplateTest.cpp)
add_executable(FooTest src/basic/template/FooTest.cpp src/basic/template/Foo.cpp)


#--------------  exception --------------

add_executable(ExceptionTest src/basic/exception/ExceptionTest.cpp src/basic/exception/Exception.cpp)
add_executable(ThrowExceptionTest src/basic/exception/ThrowExceptionTest.cpp src/basic/exception/Exception.cpp)
add_executable(TerminateTest src/basic/exception/TerminateTest.cpp)


#--------------  exception --------------

add_executable(DynamicCastTest src/basic/cast/DynamicCastTest.cpp)


#--------------  time --------------

add_executable(ChronoTest src/basic/time/ChronoTest.cpp)

#------------- file ----------------

add_executable(FileStreamTest src/basic/file/FileStreamTest.cpp)


#------------- lock ----------------

add_executable(LockTest src/basic/lock/LockTest.cpp)
add_executable(getFDCountTest src/basic/lock/getFDCount.cpp)

#------------- macro ----------------
add_executable(gCommonMacroTest src/basic/macro/CommonMacro.cpp)

#------------- meta ----------------
add_executable(HasMemberTest src/basic/meta/HasMember.cpp)

#------------- enum ----------------
add_executable(EnumTest src/basic/enum/EnumTest.cpp)

#------------- LambdaTest----------------
add_executable(LambdaTest src/basic/lambda/LambdaTest.cpp)


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

#------------- LambdaTest----------------
add_subdirectory(contrib)
add_executable(EchoServer src/poco/EchoServer.cpp)

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


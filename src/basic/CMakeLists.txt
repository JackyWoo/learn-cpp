
# --------------  type --------------
add_executable(TypeTest type/TypeTest.cpp )
add_executable(structTest type/StructTest.cpp type/Person.h type/Uu.cpp type/Color.h)
add_executable(pointerTest type/Pointer.cpp)
add_executable(ReferenceTest type/ReferenceTest.cpp)
add_executable(StringTest type/StringTest.cpp)

add_executable(MemCommitTest sys/MemCommitTest.cpp)
add_executable(ThreadScheduleTest sys/ThreadScheduleTest.cpp)

add_executable(FunctionTest sys/FunctionTest.cpp)

add_executable(Jill namespace/Jill.cpp)
add_executable(externTest type/extern/Main.cpp type/extern/Support.cpp)

# --------------  constructor --------------

add_executable(NewTest operator/NewTest.cpp)


# --------------  oop --------------

add_executable(Stock oop/Stock.h oop/Stock.cpp oop/Invoker.cpp oop/OpStock.cpp)
add_executable(MethodOverrideTest oop/MethodOverrideTest.cpp )
add_executable(PolyTest oop/PolyTest.cpp )
add_executable(PeopleTest oop/PeopleTest.cpp oop/People.cpp oop/Man.cpp)


# --------------  STL --------------

add_executable(StringTest1 stl/StringTest.cpp)
add_executable(VectorTest stl/VectorTest.cpp)
add_executable(MapTest stl/MapTest.cpp)
add_executable(MapBenchmark stl/MapBenchmark.cpp)
add_executable(ListTest stl/ListTest.cpp)
add_executable(SetTest stl/SetTest.cpp)


# --------------  Template --------------



#--------------  queue --------------

add_executable(BlockingQueueTest queue/BlockingQueueTest.cpp)
add_executable(ThreadPoolTest queue/FixedThreadPool.cpp queue/FixedThreadPoolTest.cpp)

#--------------  x_ptr --------------

add_executable(ResourceReleaseTest x_ptr/ResourceReleaseTest.cpp  oop/Stock.h  oop/Stock.cpp)
add_executable(SegFaultTest x_ptr/SegFaultTest.cpp )


add_executable(UniquePtrTest x_ptr/UniquePtrTest.cpp)
add_executable(SharedPtrTest x_ptr/SharedPtrTest.cpp)
add_executable(NullPtrTest x_ptr/NullPtrTest.cpp)

#--------------  pointer --------------



#--------------  ref --------------

add_executable(RefTest ref/RefTest.cpp)
add_executable(RefTest2 ref/RefTest2.cpp)
add_executable(RefTest3 ref/RefTest3.cpp)

#--------------  thread --------------

add_executable(ThreadTest thread/ThreadTest.cpp)

#--------------  cpp11 --------------

add_executable(BackReturnTypeTest cpp11/BackReturnTypeTest.cpp)
add_executable(DefaultTemplateArgName cpp11/DefaultTemplateArgName.cpp)
add_executable(InitObjectTest cpp11/InitObjectTest.cpp)
add_executable(MoveConstructorTest cpp11/MoveConstructorTest.cpp)
target_compile_options(MoveConstructorTest PUBLIC -std=c++11 -fno-elide-constructors)
add_executable(MoveConstructorTest2 cpp11/MoveConstructorTest2.cpp)
add_executable(MoveConstructorTest3 cpp11/MoveConstructorTest3.cpp)
add_executable(ArgDeliverTest cpp11/PerfectForwarding.cpp)
add_executable(ConstexprTest cpp11/ConstexprTest.cpp)


#--------------  operator --------------

add_executable(OperatorOverrideTest operator/OperatorOverrideTest.cpp)
add_executable(OperatorOverrideTest1 operator/OperatorOverrideTest1.cpp)

#--------------  template --------------

add_executable(ArrayTemplateTest template/ArrayTemplateTest.cpp)
add_executable(FooTest template/FooTest.cpp template/Foo.cpp)


#--------------  exception --------------

add_executable(ExceptionTest exception/ExceptionTest.cpp exception/Exception.cpp)
add_executable(ThrowExceptionTest exception/ThrowExceptionTest.cpp exception/Exception.cpp)
add_executable(TerminateTest exception/TerminateTest.cpp)


#--------------  exception --------------

add_executable(SerializeTest class/SerializeTest.cpp)
add_executable(VirtualFunctionTest class/VirtualFunctionTest.cpp)


#--------------  time --------------

add_executable(ChronoTest time/ChronoTest.cpp)

#------------- file ----------------

add_executable(FileStreamTest file/FileStreamTest.cpp)


#------------- lock ----------------

add_executable(LockTest lock/LockTest.cpp)
add_executable(getFDCountTest lock/getFDCount.cpp)

#------------- macro ----------------
add_executable(gCommonMacroTest macro/CommonMacro.cpp)

#------------- meta ----------------
add_executable(HasMemberTest meta/HasMember.cpp)
add_executable(ParameterPack meta/ParameterPack.cpp)
add_executable(EnableIfDemo meta/EnableIfDemo.cpp)

#------------- enum ----------------
add_executable(EnumTest enum/EnumTest.cpp)

#------------- LambdaTest----------------
add_executable(LambdaTest lambda/LambdaTest.cpp)

#------------- AlignmentTest----------------
add_executable(AlignmentTest memory/AlignmentTest.cpp)




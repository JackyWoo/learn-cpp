add_executable(autoVectorization autoVectorization.cpp)
target_compile_options(autoVectorization PRIVATE "-mavx512f" "-mavx512dq" "-mavx512vl" "-mavx512bw" "-mavx512cd" "-mavx512ifma" "-mavx512vbmi" -O2 -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize)

add_executable(compilerAutoVector compilerAutoVector.cpp)
#target_compile_options(compilerAutoVector PRIVATE -g -Rpass=loop-vectorize)
target_compile_options(compilerAutoVector PRIVATE -O2 -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize)

add_executable(dispatchByTarget dispatchByTarget.cpp)

add_executable(toUpperCase toUpperCase.cpp)
#target_compile_options(toUpperCase PRIVATE "-mavx512f" "-mavx512dq" "-mavx512vl" "-mavx512bw" "-mavx512cd" "-mavx512ifma" "-mavx512vbmi")

add_executable(stdvectorAutoVectorization stdvectorAutoVectorization.cpp)

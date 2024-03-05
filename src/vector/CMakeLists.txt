add_executable(compilerAutoVector compilerAutoVector.cpp)
target_compile_options(compilerAutoVector PRIVATE -g - -Rpass=loop-vectorize)
#target_compile_options(compilerAutoVector PRIVATE -O2 -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize)

add_executable(dispatchByTarget dispatchByTarget.cpp)

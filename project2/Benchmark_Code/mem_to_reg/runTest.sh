#You may need to adjust the path after -load before running this script
#   LLVM Passes for:
#   Promote memory to register: -mem2reg
make clean
clang -emit-llvm -O0 -c test.c -o test.bc
opt  -mem2reg test.bc -o mem2reg.bc
llvm-dis mem2reg.bc
llvm-dis test.bc
opt -stats -analyze -instcount test.bc -S 
opt -stats -analyze -instcount mem2reg.bc -S
lli test.bc #run unoptimized benchmark code
lli mem2reg.bc #run optimized benchmark code
make clean

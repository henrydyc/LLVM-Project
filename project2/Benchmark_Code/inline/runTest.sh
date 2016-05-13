#You may need to adjust the path after -load before running this script
#   LLVM Passes for:
#   Function Inlining: -inline
make clean
clang -emit-llvm -O0 -c test.c -o test.bc
opt -mem2reg -inline test.bc -o inline.bc
opt -mem2reg test.bc -o test.bc
llvm-dis test.bc
llvm-dis inline.bc
opt -stats -analyze -instcount test.bc -S 
opt -stats -analyze -instcount inline.bc -S
lli test.bc #run unoptimized benchmark code
lli inline.bc #run optimized benchmark code
make clean

#You may need to adjust the path after -load before running this script
#   LLVM Passes for induction variables:
#   Loop Strength Reduction: -loop-reduce
#   Loop Invariant Code Motion: -licm
make clean
clang -emit-llvm -O0 -c test.c -o test.bc
opt  -mem2reg test.bc -o test.bc
opt  -mem2reg -loop-reduce -licm test.bc -o indvars.bc
llvm-dis -f test.bc
llvm-dis -f indvars.bc
opt -stats -analyze -instcount test.bc -S
opt -stats -analyze -instcount indvars.bc -S
lli test.bc
lli indvars.bc
make clean

#You may need to adjust the path after -load before running this script
#   LLVM Passes for:
#   Reassociate Expressions: -reassociate
make clean
clang -emit-llvm -O0 -c test.c -o test.bc
opt  -mem2reg -reassociate test.bc -o reassociate.bc
opt  -mem2reg test.bc -o test.bc
llvm-dis -f test.bc
llvm-dis -f reassociate.bc
opt -stats -analyze -instcount test.bc -S
opt -stats -analyze -instcount reassociate.bc -S
lli test.bc
lli reassociate.bc
make clean

#  /*LLVM Passes for:
#  * 1. Dead Code Elimination: -dce
#  * 2. Dead Instruction Elimination: -die
#  * 3. Dead Store Elimination: -dse
#  * 4. Dead Gloabl Elimination: -globaldce
#  * 5. Dead Argument Elimination -deadargelim
#  * 6. Dead Type EliminationL: -deadtypeelim*/
make clean
clang -emit-llvm -O0 -c test.c -o test.bc
opt --mem2reg -dce -deadargelim -dse test.bc -o dce.bc
opt -mem2reg test.bc -o test.bc
llvm-dis -f test.bc
llvm-dis -f dce.bc
opt -stats -analyze -instcount test.bc -S 
opt -stats -analyze -instcount dce.bc -S
lli test.bc #run unoptimized benchmark code
lli dce.bc #run optimized benchmark code
make clean

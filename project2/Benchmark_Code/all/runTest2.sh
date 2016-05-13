#You may need to adjust the path after -load before running this script
#  /* Dead Code Elimination
#  * 1. Dead Code Elimination: -dce
#  * 2. Dead Instruction Elimination: -die
#  * 3. Dead Store Elimination: -dse
#  * 4. Dead Gloabl Elimination: -globaldce
#  * 5. Dead Argument Elimination -deadargelim
#  * 6. Dead Type EliminationL: -deadtypeelim*/

#   Simple Constant Propagation: -constprop
#   Reassociate Expressions: -reassociate
#   LLVM Passes for induction variables:
#   Loop Strength Reduction: -loop-reduce
#   Loop Invariant Code Motion: -licm

make clean
clang -emit-llvm -O0 -c test2.c -o test2.bc
clang -emit-llvm -O1 -c test2.c -o all.bc
opt  -mem2reg -inline -loop-simplify  -reassociate -constprop -sccp -deadargelim -dce -indvars -loop-reduce -licm  -adce test2.bc -o all.bc #Long sequence
opt  -mem2reg test2.bc -o test2.bc
llvm-dis -f test2.bc
llvm-dis -f all.bc
opt -stats -analyze -instcount test2.bc -S
opt -stats -analyze -instcount all.bc -S
lli all.bc
lli test2.bc
make clean

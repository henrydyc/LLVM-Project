#You may need to adjust the path after -load before running this script
#   LLVM Passes for:
#   Simple Constant Propagation: -constprop
make clean
clang -emit-llvm -O0 -c test.c -o test.bc
opt -mem2reg -constprop test.bc -o constprop.bc
opt -mem2reg test.bc -o test.bc
llvm-dis test.bc
llvm-dis constprop.bc
opt -stats -analyze -instcount test.bc -S 
opt -stats -analyze -instcount constprop.bc -S
lli test.bc #run unoptimized benchmark code
lli constprop.bc #run optimized benchmark code
make clean

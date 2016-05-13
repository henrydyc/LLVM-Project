# Makefile for tests; generates unoptimized .ll IR for all tests

# Test files
FILES = test.bc callgraph.png

##
CLANG = clang
CLANG_FLAGS = -emit-llvm -O0
DIS = llvm-dis
LLC = llc

all: $(FILES)

clean:
	rm -f *.bc *.ll *.s *.out *.dot *.png

test.bc:
	$(CLANG) $(CLANG_FLAGS) -c -g test.c -o test.bc
	$(DIS) -f test.bc

callgraph.png:
	opt -dot-callgraph test.bc
	dot -Tpng callgraph.dot > test_callgraph.png

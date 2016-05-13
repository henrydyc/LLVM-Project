# Makefile for tests; generates unoptimized .ll IR for all tests

# Test files
FILES = test2.bc callgraph.png

##
CLANG = clang
CLANG_FLAGS = -emit-llvm -O0
DIS = llvm-dis
LLC = llc

all: $(FILES)

clean:
	rm -f *.bc *.ll *.s *.out *.dot *.png

test2a.bc:
	$(CLANG) $(CLANG_FLAGS) -c -g test2a.c -o test2a.bc
test2b.bc:
	$(CLANG) $(CLANG_FLAGS) -c -g test2b.c -o test2b.bc

test2.bc: test2a.bc test2b.bc
	llvm-link test2a.bc test2b.bc -o test2.bc
	$(DIS) -f test2.bc

callgraph.png:
	opt -dot-callgraph test2.bc
	dot -Tpng callgraph.dot > test_callgraph.png

# Makefile for tests; generates unoptimized .ll IR for all tests

# Test files
FILES = test.bc

##
CLANG = clang
CLANG_FLAGS = -emit-llvm -O0
DIS = llvm-dis
LLC = llc

all: $(FILES)

clean:
	rm -f *.bc *.ll *.s *.out

test.bc:
	$(CLANG) $(CLANG_FLAGS) -c test.c -o test.bc
	$(DIS) -f test.bc

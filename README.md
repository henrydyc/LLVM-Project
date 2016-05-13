#LLVM-Project
This repo consists of two projects that explore a small part of the LLVM functionality and infrastructure.

**Project 1 (Analysis Pass)**  
This project performs the following analysis:

1. *Call Graph Analysis:* Here the Caller-callee relationship (the call graph) will be printed, this includes line number of each call and the arguments being accepted by the callee. If there is an error, a mismatch of function parameter types, an error message will be printed. 
2. *Function Call Statistics:* Counts the number of calls to each function in the source file.

**Project 2 (LLVM Transformation Pass Benchmark Study)**  
This project investigates the following aspects of a wide range of LLVM transformation passes on the *C language*: 

1. The nature of the transformation done by each pass. 
2. The efficacy of the resultant optimization measured by the number of LLVM IR instructions as well as code execution wall time.
3. The effect of using a combination of different passes and the possible optimal sequence to apply these passes for code optimization.

**More details can be seen in the project report file included in this repo

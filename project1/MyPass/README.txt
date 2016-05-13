List of files in this folder:
1. MyPass.cpp
2. Makefile (for making MyPass)
3. Test files (two folders: test1/ and test2/):
    Each test folder contains .c source code and a Makefile
    The Makefile also contains commands to generate the call graph picture.

===========================================================    
I. How to make the pass:

Please create a folder 'MyPass' in your llvm/lib/Transforms directory, and place the Makefile 
and MyPass.cpp in this path:
someParentDirectory/llvm/lib/Transforms/MyPass/

Then within the MyPass folder, type 'make' to make and install MyPass in your llvm environment.

===========================================================
II. How to run the pass on your test files:
1. Please include the -g tag when compiling the .c files to enable line number
2. After compilation, please make sure you have .bc file in your current directory, say, test.bc
3. To run MyPass on test.bc , use the following command:

opt -load someParentDirectory/llvm/Debug+Asserts/lib/MyPass.dylib -MyPass -disable-output test.bc

The result of the pass will be printed to the screen.

===========================================================
III. How to read the pass output:
The output is in two parts:
1. Call Graph Analysis:
    Here the Caller-callee relationship (the call graph) will be printed. It has the line number of
    each call on the callee function, together with the arguments being accepted by the callee.
    If there is an error, for example, a mismatch of function parameter types, an error message will
    be printed.
2. Function Call Statistics:
    Here a list of functions and the number of calls to each function will be displayed.


============================================================
IV. Approach:
In this assignment, to construct the call graph, my pass ("MyPass") inherits from ModulePass,
and it traverses each functions, and within each function, it traverses each instructions to 
locate "Call instructions" from which the callee info can be extracted.
Therefore the function call statistics reflects the actual number of times this function is being 
called (statically, of course). 
In the debug mode (with -g option), a function “llvm.dg.declare” will be generated in the call instructions,
but I chose to ignore this function in my analysis because this is not native to my code.

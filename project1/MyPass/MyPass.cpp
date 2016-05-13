/* An LLVM Pass that does Call graph analysis and Error detection
 * Author: Yichao Dong
 * Email: yichaodo@usc.edu
 * Please read README.txt file first for compiling instructions
 * */
#define DEBUG_TYPE "MyPass"
#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Attributes.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include <vector>
#include <string>
#include <assert.h>
using namespace llvm;
namespace {
    struct MyPass: public ModulePass {
        static char ID;
        std::map<std::string, int> functionCallCounter; /*counts the static number that a function appears*/
        MyPass() : ModulePass(ID) {}
        bool runOnModule(Module &M);
        bool runOnFunction(Function &F);
    };
}

char MyPass::ID = 0;
static RegisterPass<MyPass> X("MyPass", "cs561 project1 pass");
// static int numFunctions =0;


bool MyPass::runOnModule(Module &M){
    errs() << "\n/********************* Start of MyPass Analysis *********************/\n";

    for(Module::iterator F = M.begin(), e= M.end(); F!=e; ++F){
        std::string funcName = F->getName().str();
        if (funcName == "llvm.dbg.declare") continue;
        if (funcName == "main"){
            functionCallCounter[funcName] = 1;
        }else{
            functionCallCounter[funcName] = 0;
        }
    }
    // errs()<<"Total Function Count: "<< numFunctions<<"\n\n";
    errs() << "\n\n/***** Call Graph Analysis *****/\n";
    bool modified;
    for(Module::iterator F = M.begin(), e= M.end(); F!=e; ++F){
        modified |= runOnFunction(*F);
    }

    errs() << "\n/***** Function call statistics: *****/\n";
    errs() << "List of Function Calls:\n";

    for(Module::iterator F = M.begin(), e= M.end(); F!=e; ++F){
        std::string funcName = F->getName().str();
        if (funcName == "llvm.dbg.declare") continue;
        Function::ArgumentListType &argList = F->getArgumentList();
        errs() << funcName <<" (";
        if (argList.size() <= 1){
            for (auto & a: argList)
                errs() << *(a.getType());
        } else {
            auto iter = argList.begin();
            errs()<< *(iter->getType());
            ++iter;
            for(auto e = argList.end(); iter != e; ++iter){
                errs() <<", "<< *(iter->getType());
            }
        }
        int nCalls = functionCallCounter[funcName];
        errs() <<") : "<< nCalls <<"\n";
    }

    errs() << "\n/*********************** End of MyPass Analysis *********************/\n\n";
    return modified;
}

// ArgumentListType arg_list; /*ArgumentListType is plist <Argument>*/
bool MyPass::runOnFunction(Function &F) {
    std::string funcName = F.getName().str();
    if (funcName == "llvm.dbg.declare") return false;
    errs() << "Within Function \'"<< funcName <<"\':\n";
    bool hasCallee = false;
    /*Check if F is a library defined function: it will have no basic blocks*/
    Function::iterator bb = F.begin();
    if (bb == F.end()){
        errs() << "No basic block is identified.\n";
        errs() << "\'"<< funcName <<"\' is either a library function or a user-defined function that lacks definition.\n\n";
        return false;
    }
    for (Function::iterator e = F.end(); bb != e; ++bb){
        /*For functions that call other functions in its scope, we look at them*/
        for (BasicBlock::iterator i = bb->begin(), e = bb->end(); i !=e; ++i){
            if (isa<CallInst>(i)){
                llvm::Instruction &instr = *i;
                CallInst& ci = static_cast<CallInst&>(instr);
                Function* fun = ci.getCalledFunction();
                bool hasError = false;
                if(!fun){
                    fun = dyn_cast<Function>(ci.getCalledValue()->stripPointerCasts());
                    hasError = true;
                    // errs()<< *(ci.getOperand(ci.getNumOperands())->stripPointerCasts());
                }
                if (fun->getName().str() == "llvm.dbg.declare") continue;
                hasCallee = true;
                Function::ArgumentListType &argList = fun->getArgumentList();
                /*Get the line number of this instruction*/
                if (MDNode *N = instr.getMetadata("dbg")) {  // Here I is an LLVM instruction
                    DILocation Loc(N);                      // DILocation is in DebugInfo.h
                    unsigned lineNumber = Loc.getLineNumber();
                    if (hasError){
                        errs()<<"Error: Call on Function \'"<< fun->getName() <<"\' on Line "
                            <<lineNumber <<" does not match function declaration.\n";
                        // errs() << "Casted Instruction: "<<instr<<"\n";
                        errs() << "Function \'"<< fun->getName() <<"\' expects "
                            <<argList.size()<<" argument(s)";
                    }else{
                        errs()<< "Call on Function \'" <<fun->getName()
                            <<"\' on Line "<< lineNumber
                            <<" with "<<argList.size()<<" argument(s)";
                    }
                } else {

                    if (hasError){
                        errs()<<"Error: Call on Function \'"<< fun->getName() 
                            <<"\' does not match function declaration.\n";
                        // errs() << "Casted Instruction: "<<instr<<"\n";
                        errs() << "Function \'"<< fun->getName() <<"\' expects "
                            <<argList.size()<<" argument(s)";
                    } else {
                        errs()<< "Call on Function \'" <<fun->getName()
                            <<"\' with "<<argList.size()<<" argument(s)";
                    }
                }
                if (argList.size()>0){
                    errs()<<":\n";
                    int arg_count =1;
                    for (auto & a : argList){
                        errs() << "Argument "<<arg_count++<<" Type: "<<*(a.getType())<<"\n";
                    }
                } else {
                    errs() <<".\n";
                }

                /*Tally the count*/
                functionCallCounter[fun->getName().str()] += 1;
            }
        }
    }

    
    if (!hasCallee){
        errs()<<"Function \'"<<funcName<<"\' does not call other functions in its scope.\n";
    }
    errs()<<"\n";

    return false;
}

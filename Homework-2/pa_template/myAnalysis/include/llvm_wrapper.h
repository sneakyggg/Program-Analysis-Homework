#ifndef _LLVM_WRAPPER_H_
#define _LLVM_WRAPPER_H_
#include <string>
#include <set>
#include <memory>
#include "llvm/Support/raw_ostream.h"
#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IntrinsicInst.h"

using namespace std;

namespace llvm 
{
    class LLVMContext;
    class Module;
    class Function;
    class GlobalVariable;
    class MemoryBuffer;
}

class LLVM 
{
public:
    typedef set<llvm::GlobalVariable*>::iterator gv_iterator;
    typedef set<llvm::Function*>::iterator func_iterator;

public:
    LLVM(const string &bcFile)
    {
        Context = make_unique<llvm::LLVMContext>();

        auto bufferOrError = llvm::MemoryBuffer::getFile(bcFile);
        if (!bufferOrError) 
        {
            llvm::errs() << "Error reading bitcode file: " << bcFile << "\n";
            return;
        }
        unique_ptr<llvm::MemoryBuffer> buffer = move(bufferOrError.get());

        auto moduleOrError = llvm::parseBitcodeFile(buffer->getMemBufferRef(), *Context);
        if (!moduleOrError) 
        {
            llvm::errs() << "Error parsing bitcode file: " << bcFile << "\n";
            return;
        }
        ModulePtr = move(moduleOrError.get());

        loadFunctions();
        loadGlobals();
    }

    ~LLVM() {}

    // Iterators over the global variables.
    gv_iterator gv_begin() { return globals.begin(); }
    gv_iterator gv_end()   { return globals.end(); }

    // Iterators over the functions.
    func_iterator func_begin() { return functions.begin(); }
    func_iterator func_end()   { return functions.end(); }

    llvm::Module* getModule() const { return ModulePtr.get(); }

    inline string getValueLabel(const llvm::Value* V) 
    {
        string label;
        llvm::raw_string_ostream rso(label);
        V->print(rso);
        return rso.str();
    }

private:
    void loadFunctions() 
    {
        for (llvm::Function &F : *ModulePtr) 
        {
            functions.insert(&F);
        }
    }

    void loadGlobals() 
    {
        for (llvm::GlobalVariable &GV : ModulePtr->globals()) 
        {
            globals.insert(&GV);
        }
    }

private:
    unique_ptr<llvm::LLVMContext> Context;
    unique_ptr<llvm::Module> ModulePtr;

    set<llvm::GlobalVariable*> globals;
    set<llvm::Function*> functions;
};

#endif

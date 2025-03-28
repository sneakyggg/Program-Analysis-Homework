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
    LLVM() {}
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
        if (auto *GV = llvm::dyn_cast<llvm::GlobalVariable>(V)) 
        {
            return GV->getName().str();
        }

        if (auto *F = llvm::dyn_cast<llvm::Function>(V))
        {
            return F->getName().str();
        }

        std::string label;
        llvm::raw_string_ostream rso(label);
        V->print(rso);

        size_t pos = label.find(", align ");
        if (pos != string::npos)
        {
            label.erase(pos);
        }

        pos = label.find(", !dbg ");
        if (pos != string::npos)
        {
            label.erase(pos);
        }
        
        const std::string token = "noalias ";
        pos = label.find(token);
        if (pos != string::npos) {
            label.erase(pos, token.size());
        }
        return label;
    }

    inline bool isAddressOf(llvm::Instruction *I)
    {
        // 1) p = alloca
        if (llvm::isa<llvm::AllocaInst>(I))
            return true;

        // 2) p = getelementptr @Global
        if (auto *gep = llvm::dyn_cast<llvm::GetElementPtrInst>(I))
        {
            llvm::Value *base = gep->getOperand(0);
            if (llvm::isa<llvm::GlobalVariable>(base))
            {
                return true;
            }
        }

        // 3) p = inttoptr x
        if (llvm::isa<llvm::IntToPtrInst>(I))
        {
            return true;
        }

        // Otherwise, not treated as address-of
        return false;
    }


    inline std::pair<llvm::Value*, llvm::Value*> getOperandsAddressOf(llvm::Instruction *I)
    {
        if (auto *allocaInst = llvm::dyn_cast<llvm::AllocaInst>(I)) 
        {
            return std::make_pair(I, I);
        }

        return std::make_pair(nullptr, nullptr);
    }


    inline bool isAssignment(llvm::Instruction *I)
    {
        if (auto *castInst = llvm::dyn_cast<llvm::CastInst>(I)) 
        {
            if (castInst->getSrcTy()->isPointerTy() && castInst->getDestTy()->isPointerTy()) 
            {
                return true;
            }
        }

        if (llvm::dyn_cast<llvm::GetElementPtrInst>(I)) 
        {
            return true;
        }

        return false;
    }

    inline std::pair<llvm::Value*, llvm::Value*> getOperandsAssignment(llvm::Instruction *I)
    {
        if (auto *castInst = llvm::dyn_cast<llvm::BitCastInst>(I)) 
        {
            llvm::Value *srcVal = castInst->getOperand(0);
            llvm::Value *dstVal = castInst;
            return std::make_pair(srcVal, dstVal);
        }

        if (auto *gep = llvm::dyn_cast<llvm::GetElementPtrInst>(I))
        {
            llvm::Value *basePtr = gep->getPointerOperand();
            llvm::Value *dstVal  = gep;
            return std::make_pair(basePtr, dstVal);
        }

        return std::make_pair(nullptr, nullptr);
    }


    inline bool isStore(llvm::Instruction *I)
    {
        return llvm::isa<llvm::StoreInst>(I);
    }

    inline std::pair<llvm::Value*, llvm::Value*> getOperandsStore(llvm::Instruction *I)
    {
        if (auto *storeInst = llvm::dyn_cast<llvm::StoreInst>(I)) 
        {
            llvm::Value *srcVal     = storeInst->getValueOperand();
            llvm::Value *pointerVal = storeInst->getPointerOperand();
            return std::make_pair(pointerVal, srcVal);
        }

        return std::make_pair(nullptr, nullptr);
    }


    inline bool isLoad(llvm::Instruction *I)
    {
        return llvm::isa<llvm::LoadInst>(I);
    }

    inline std::pair<llvm::Value*, llvm::Value*> getOperandsLoad(llvm::Instruction *I)
    {
        if (auto *loadInst = llvm::dyn_cast<llvm::LoadInst>(I)) 
        {
            llvm::Value *pointerVal = loadInst->getPointerOperand();
            llvm::Value *dstVal     = loadInst; 
            return std::make_pair(pointerVal, dstVal);
        }

        return std::make_pair(nullptr, nullptr);
    }

    inline bool isMemAlloc(llvm::Function *callee)
    {
        if (!callee)
        {
            return false;
        }

        // Common C allocation functions
        const std::set<std::string> cAllocFuncs = 
        {
            "malloc",
            "calloc",
            "realloc",
            "aligned_alloc",
            "valloc",
            "memalign",
            "posix_memalign"
        };

        // Common C++ allocation functions: operator new, operator new[]
        const std::set<std::string> cppAllocFuncs = 
        {
            "_Znw",
            "_Zna",
            "_Znwj",
            "_Znaj",
            "operator new",
            "operator new[]"
        };

        std::string calleeName = callee->getName().str();
        if (cAllocFuncs.count(calleeName) || cppAllocFuncs.count(calleeName))
        {
            return true;
        }

        return false;
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

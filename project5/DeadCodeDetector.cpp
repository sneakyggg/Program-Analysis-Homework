#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"       
#include "llvm/Transforms/Utils/PromoteMemToReg.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;

static inline bool isValueProducing(const Instruction *I) {
  return !I->getType()->isVoidTy();
}

/// Best‑effort source line lookup (0 if unavailable).
static inline unsigned getLine(const Instruction &I) {
  if (DebugLoc DL = I.getDebugLoc())
    return DL.getLine();
  return 0;
}

namespace {
class ProgramAnalysis : public PassInfoMixin<ProgramAnalysis> {
private:
  // Statistics counters
public:
  // New Pass Manager interface
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {  
    errs() << "==== Running ====\n";
    // Live‑out sets per basic block.
    for (Function &F : M) {
      if (F.isIntrinsic())
        {continue;}
        SmallVector<AllocaInst*, 16> Allocas;
        for (BasicBlock &BB : F)
          for (Instruction &I : BB)
            if (auto *AI = dyn_cast<AllocaInst>(&I))
              if (AI->isStaticAlloca())          
                Allocas.push_back(AI);
    
        if (!Allocas.empty()) {
          DominatorTree DT(F);                   
          PromoteMemToReg(Allocas, DT);
        }

    DenseMap<const BasicBlock *, SmallPtrSet<const Value *, 8>> LiveOut;
    for (const BasicBlock &BB : F)
      LiveOut[&BB] = {};

    bool Changed = true;
    while (Changed) {
      Changed = false;

      // Iterate blocks in any order (convergence guaranteed for finite lattice).
      for (const BasicBlock &BB : F) {
        SmallPtrSet<const Value *, 8> NewLive;

        // Successor live‑in → our live‑out (backwards analysis).
        for (const BasicBlock *Succ : successors(&BB))
          NewLive.insert(LiveOut[Succ].begin(), LiveOut[Succ].end());

        // Walk instructions backwards.
        for (auto I = BB.rbegin(), E = BB.rend(); I != E; ++I) {
          const Instruction &Inst = *I;

          // KILL – remove definition.
          if (isValueProducing(&Inst))
            NewLive.erase(&Inst);

          // GEN – add all operand uses.
          for (const Use &Op : Inst.operands())
            if (isa<Instruction>(Op) || isa<Argument>(Op))
              NewLive.insert(Op.get());
        }

        // Fixed‑point step.
        if (NewLive != LiveOut[&BB]) {
          LiveOut[&BB] = std::move(NewLive);
          Changed = true;
        }
      }
    }

    // ── Reporting ────────────────────────────────────────────────────────────
    errs() << "[DeadCodeDetector] Function " << F.getName() << "\n";
    bool Any = false;

    for (const BasicBlock &BB : F) {
      SmallPtrSet<const Value *, 8> CurLive = LiveOut[&BB];

      for (auto I = BB.rbegin(), E = BB.rend(); I != E; ++I) {
        Instruction &Inst = const_cast<Instruction &>(*I);

        if (isValueProducing(&Inst) && !CurLive.contains(&Inst)) {
          Any = true;
          errs() << "  -> Dead def at line " << getLine(Inst) << ": " << Inst
                 << "\n";
        }

        // Update CurLive moving backward.
        if (isValueProducing(&Inst))
          CurLive.erase(&Inst);
        for (const Use &Op : Inst.operands())
          if (isa<Instruction>(Op) || isa<Argument>(Op))
            CurLive.insert(Op.get());
      }
    }
  }
  errs() << "==== Done ====\n";
    // Read‑only analysis – nothing is modified.
    return PreservedAnalyses::all();
}
};

} // end anonymous namespace

// New pass manager registration
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "ProgramAnalysis", LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, ModulePassManager &MPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "program-analysis") {
            MPM.addPass(ProgramAnalysis());
            return true;
          }
          return false;
        });
    }
  };
}
/**
 * @file nep_interface.cpp
 * @brief check if there is unimplemented NEP interface
 * @ref NEP "https://github.com/near/NEPs"
 *
 */
#include "near_core.h"

#include <set>
#include <unordered_map>

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Value.h"
#include "llvm/Pass.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Regex.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

static llvm::cl::opt<unsigned> nepId("nep-id", llvm::cl::desc("Specify the id of nep, refer to https://github.com/near/NEPs for more"), llvm::cl::value_desc("id"));

/**
 * @example {
 *     {nep-id, {func1, func2, func3, ...}},
 * }
 *
 */
static const std::unordered_map<unsigned, std::set<llvm::StringRef>> positionalFuncsMap = {
    {141, {"ft_transfer", "ft_transfer_call", "ft_on_transfer", "ft_total_supply", "ft_balance_of"}},
    {145, {"storage_deposit", "storage_withdraw", "storage_unregister", "storage_balance_bounds", "storage_balance_of"}},
};

/**
 * @example {
 *     {
 *         nep-id,
 *         {
 *             {func1_name1, func1_name2},
 *             {func2_name1, ...},
 *         },
 *     },
 * }
 *
 */
static const std::unordered_map<unsigned, std::set<std::set<llvm::StringRef>>> optionalFuncsMap = {
    {
        141,
        {
            {"ft_resolve_transfer", "resolve_transfer"},
        },
    },
    {
        145,
        {},
    },
};

namespace {
    struct UnsavedChanges : public llvm::ModulePass {
        static char ID;

      private:
        llvm::raw_fd_ostream *os = nullptr;

      public:
        UnsavedChanges() : ModulePass(ID) {
            std::error_code EC;

            os = new llvm::raw_fd_ostream(std::string(getenv("TMP_DIR")) + std::string("/.nep-interface.tmp"), EC, llvm::sys::fs::OpenFlags::OF_Append);
        }
        ~UnsavedChanges() { os->close(); }

        bool runOnModule(llvm::Module &M) override {
            using namespace llvm;

            if (positionalFuncsMap.count(nepId.getValue()) == 0)
                Rustle::Logger().Warning("Invalid nep-id: ", nepId.getValue());

            CallGraph CG(M);

            std::set<StringRef> funcSet;

            for (auto &F : M.functions()) {
                if (!Rustle::debug_check_all_func && Rustle::regexForLibFunc.match(F.getName()))
                    continue;
                funcSet.insert(F.getName());
            }

            auto const &positionalFuncs = positionalFuncsMap.at(nepId.getValue());
            auto const &optionalFuncs   = optionalFuncsMap.at(nepId.getValue());

            for (auto const &func : positionalFuncs) {
                if (funcSet.count(func)) {
                    Rustle::Logger().Info("Implemented:   ", func);
                } else {
                    Rustle::Logger().Warning("Unimplemented: ", func);
                }
            }
            for (auto const &funcGroup : optionalFuncs) {
                for (auto const &func : funcGroup) {
                    if (funcSet.count(func)) {
                        Rustle::Logger().Info("Implemented:   ", func);
                        break;  // skip current group
                    }
                }
            }

            return false;
        }
    };
}  // namespace

char UnsavedChanges::ID = 0;

static llvm::RegisterPass<UnsavedChanges> X("nep-interface", "", false /* Only looks at CFG */, false /* Analysis Pass */);
static llvm::RegisterStandardPasses Y(llvm::PassManagerBuilder::EP_EarlyAsPossible, [](const llvm::PassManagerBuilder &Builder, llvm::legacy::PassManagerBase &PM) { PM.add(new UnsavedChanges()); });
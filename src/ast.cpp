#include "ast.h"

#if defined(_MSC_VER)
#pragma warning(push, 0)
#endif

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include "deviant_llvm.h"

namespace deviant {
// TODO: equal to block?
llvm::Value* Program::generateCode(DeviantLLVM& context) {
  llvm::Value* last = nullptr;
  for (size_t i = 0; i < statements_.size(); ++i) {
    auto stmt = statements_[i].get();
    last = stmt->generateCode(context);
  }
  return last;
}
// TODO: remove
llvm::Value* AstNode::generateCode(DeviantLLVM& context) {
  return llvm::ConstantInt::get(context.getGenericIntegerType(), 0, true);
}

llvm::Value* Integer::generateCode(DeviantLLVM& context) {
  return llvm::ConstantInt::get(context.getGenericIntegerType(), value_, true);
}

llvm::Value* Identifier::generateCode(DeviantLLVM& context) {
  // a usual stack variable
  llvm::AllocaInst* alloc = context.findVariable(name_);
  if (alloc != nullptr) {
    return new llvm::LoadInst(alloc->getAllocatedType(), alloc, name_, false,
                              context.currentBlock());
  }
}

llvm::Value* VariableDeclaration::generateCode(DeviantLLVM& context) {
  // return context.getBuilder()->CreateAlloca();
}

llvm::Value* Assignment::generateCode(DeviantLLVM& context) {
  return nullptr;
  // return context.getBuilder()->CreateAlloca();
}

llvm::Value* Block::generateCode(DeviantLLVM& context) {
  llvm::Value* last = nullptr;
  for (size_t i = 0; i < statements_.size(); ++i) {
    auto stmt = statements_[i].get();
    last = stmt->generateCode(context);
  }
  return last;
}

llvm::Value* ReturnStatement::generateCode(DeviantLLVM& context) {
  if (ret_expr_) {
    llvm::Value* ret = ret_expr_->generateCode(context);
    if (ret == nullptr)
      return nullptr;
    return context.getBuilder()->CreateRet(ret);
  } else {
    return nullptr;
  }
}

llvm::Value* FunctionStatement::generateCode(DeviantLLVM& context) {
  auto fn = context.getModule()->getFunction(fn_name_);

  // TODO: remove hardcode
  auto fn_type = llvm::FunctionType::get(/*return type*/
                                         context.getBuilder()->getInt32Ty(),
                                         /*vararg*/ false);

  // if not, allocate the function
  if (!fn) {
    fn = llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage,
                                fn_name_, *context.getModule());
    verifyFunction(*fn);
  }

  // createFunctionBlock(fn);
  auto entry =
      llvm::BasicBlock::Create(context.getGlobalContext(), "entry", fn);
  context.getBuilder()->SetInsertPoint(entry);

  body_->generateCode(context);

  return fn;
}

llvm::Value* FunctionCall::generateCode(DeviantLLVM& context) {
  // args
  std::vector<llvm::Value*> args;

  return context.getBuilder()->CreateCall(
      context.getModule()->getFunction(fn_name_), args);
}
}  // namespace deviant
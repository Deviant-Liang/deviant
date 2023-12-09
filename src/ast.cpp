#include "ast.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

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
    // builder_->CreateRet(ret_val);
    verifyFunction(*fn);
  }

  // createFunctionBlock(fn);
  auto entry =
      llvm::BasicBlock::Create(context.getGlobalContext(), "entry", fn);
  context.getBuilder()->SetInsertPoint(entry);

  llvm::IRBuilder builder(entry);
  builder.CreateRet(builder.getInt32(42));

  return fn;
}
}  // namespace deviant
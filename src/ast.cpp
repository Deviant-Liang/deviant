#include "ast.h"
#include "deviant_llvm.h"

namespace deviant {
// TODO: remove
llvm::Value* AstNode::generateCode(DeviantLLVM& context) {
  return llvm::ConstantInt::get(context.getGenericIntegerType(), 0, true);
}

llvm::Value* Integer::generateCode(DeviantLLVM& context) {
  return llvm::ConstantInt::get(context.getGenericIntegerType(), value_, true);
}
}  // namespace deviant
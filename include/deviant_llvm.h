#ifndef __DEVIANT_LLVM__
#define __DEVIANT_LLVM__

#include <memory>
#include <string>
#include <vector>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

#include "ast.h"
#include "parser.h"

namespace deviant {

class DeviantLLVM {
 public:
  DeviantLLVM();

  void execute(const std::string& program) {
    // parse the program
    parser_ = std::make_unique<Parser>(program);
    auto ast = parser_->parse();

    // compile to LLVM IR
    compile(*ast);

    // print generated code
    module_->print(llvm::outs(), nullptr);
    printf("\n");

    // save module IR to file
    saveModuleToFile("./out.ll");
  }

  llvm::LLVMContext& getGlobalContext() { return llvm_context_; }

  llvm::Type* getGenericIntegerType() {
    return llvm::Type::getInt32Ty(getGlobalContext());
  }

  llvm::Module* getModule() { return module_.get(); }

 private:
  void initModule();

  void saveModuleToFile(const std::string& filename);

  void compile(const AstNode& ast) {
    // create main function
    fn_ = createFunction(
        "main", llvm::FunctionType::get(/*return type*/ builder_->getInt32Ty(),
                                        /*vararg*/ false));

    // compile main body
    // gen(ast);

    // cast to i32 to return from main
    builder_->CreateRet(builder_->getInt32(0));
  }

  // main compiler loop
  llvm::Value* gen(const AstNode& ast) {
    // return builder_->getInt32(42);

    // strings
    auto str = builder_->CreateGlobalStringPtr("Hello, world!\n");

    // call to printf
    auto print_fn = module_->getFunction("printf");

    // args
    std::vector<llvm::Value*> args{str};

    return builder_->CreateCall(print_fn, args);
  }

  void setupExternFunctions() {
    // i8* to substitute for char*, void*, etc
    auto byte_ptr_Ty = builder_->getInt8Ty()->getPointerTo();

    // int print(const char* format, ...)
    module_->getOrInsertFunction(
        "printf",
        llvm::FunctionType::get(/*return type*/ builder_->getInt32Ty(),
                                /*format arg*/ byte_ptr_Ty, /*vararg*/ true));
  }

  llvm::Function* createFunction(const std::string& fn_name,
                                 llvm::FunctionType* fn_type) {
    // function prototype might already be defined
    auto fn = module_->getFunction(fn_name);

    // if not, allocate the function
    if (!fn) {
      fn = createFunctionPrototype(fn_name, fn_type);
    }

    createFunctionBlock(fn);
    return fn;
  }

  llvm::Function* createFunctionPrototype(const std::string& fn_name,
                                          llvm::FunctionType* fn_type) {
    auto fn = llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage,
                                     fn_name, *module_);
    verifyFunction(*fn);

    return fn;
  }

  // create function block
  void createFunctionBlock(llvm::Function* fn) {
    auto entry = createBB("entry", fn);
    builder_->SetInsertPoint(entry);
  }

  llvm::BasicBlock* createBB(const std::string& name,
                             llvm::Function* fn = nullptr) {
    return llvm::BasicBlock::Create(*context_, name, fn);
  }

  std::unique_ptr<Parser> parser_;

  // currently complier function
  llvm::Function* fn_;

  llvm::LLVMContext llvm_context_;

  std::unique_ptr<llvm::LLVMContext> context_;

  std::unique_ptr<llvm::Module> module_;

  std::unique_ptr<llvm::IRBuilder<>> builder_;
};

}  // namespace deviant

#endif  // __DEVIANT_LLVM__
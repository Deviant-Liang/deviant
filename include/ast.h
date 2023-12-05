#ifndef __AST__
#define __AST__

#include <memory>
#include <string>
#include <vector>

#include "llvm/IR/Value.h"

#define STR_EXPRESSTION "Expression"
#define STR_STATEMENT "Statement"

namespace deviant {

class DeviantLLVM;

class AstNode {
 public:
  enum class Type {
    PROGRAM,
    EXPRESSTION,
    STATEMENT,
    INTEGER,
    DECIMAL,
    BOOLEAN,
    IDENTIFIER
  };
  virtual ~AstNode() = default;

  // TODO: pure virtual
  virtual llvm::Value* generateCode(DeviantLLVM& context);

  virtual Type type() = 0;

  virtual std::string toString() = 0;
};

class Expression : public AstNode {
 public:
  ~Expression() override = default;
  // llvm::Value* generateCode(DeviantLLVM& context) override;
  Type type() override { return Type::EXPRESSTION; }
  std::string toString() override { return STR_EXPRESSTION; }
};

class Statement : public Expression {
 public:
  ~Statement() override = default;
  // llvm::Value* generateCode(DeviantLLVM& context) override;
  Type type() override { return Type::EXPRESSTION; }
  std::string toString() override { return STR_STATEMENT; }
};

class Program : public AstNode {
 public:
  ~Program() override = default;
  // llvm::Value* generateCode(DeviantLLVM& context) override;
  Type type() override { return Type::PROGRAM; }
  std::string toString() override { return "Program"; }

  void pushBack(std::unique_ptr<Statement>&& statement) {
    statements_.emplace_back(std::move(statement));
  }

 private:
  std::vector<std::unique_ptr<Statement>> statements_;
};

class Integer : public Expression {
 public:
  explicit Integer(int value) : value_(value) {}
  ~Integer() override = default;
  llvm::Value* generateCode(DeviantLLVM& context) override;
  Type type() override { return Type::INTEGER; }
  std::string toString() override { return " "; }

 private:
  int value_;
};

class Identifier : public Expression {
 public:
  ~Identifier() override = default;
  // llvm::Value* generateCode(DeviantLLVM& context) override;
  Type type() override { return Type::IDENTIFIER; }

 private:
};

class Block : public Expression {
 public:
  // StatementList statements;

  Block() = default;
  ~Block() override {
    // for (auto i : statements) {
    //   delete i;
    // }
    // statements.clear();
  }

  // llvm::Value* generateCode(DeviantLLVM& context) override;
  Type type() override { return Type::EXPRESSTION; }
  std::string toString() override { return "block "; }
  // void Accept(Visitor& v) override { v.VisitBlock(this); }
};

}  // namespace deviant

#endif  // __AST__
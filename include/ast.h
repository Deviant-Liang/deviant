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
  llvm::Value* generateCode(DeviantLLVM& context) override = 0;
  Type type() override { return Type::EXPRESSTION; }
  std::string toString() override { return STR_EXPRESSTION; }
};

class Statement : public Expression {
 public:
  ~Statement() override = default;
  llvm::Value* generateCode(DeviantLLVM& context) override = 0;
  Type type() override { return Type::EXPRESSTION; }
  std::string toString() override { return STR_STATEMENT; }
};

class Program : public AstNode {
 public:
  ~Program() override = default;
  llvm::Value* generateCode(DeviantLLVM& context) override;
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
  std::string toString() override { return "identifier"; }

  const std::string& getName() { return name_; }

 private:
  std::string name_;
};

class LetStatement : public Statement {
 public:
  ~LetStatement() override = default;
  Type type() override { return Type::STATEMENT; }
  std::string toString() override { return "let"; }

 private:
  std::unique_ptr<Identifier> identifier_;
  std::unique_ptr<Expression> expr_;
};

class Block : public Expression {
 public:
  Block() = default;
  ~Block() override = default;

  Type type() override { return Type::EXPRESSTION; }
  llvm::Value* generateCode(DeviantLLVM& context) override;
  std::string toString() override { return "block"; }
  void insertStatement(std::unique_ptr<Statement>&& stmt) {
    statements_.emplace_back(std::move(stmt));
  }

 private:
  std::vector<std::unique_ptr<Statement>> statements_;
};

class ReturnStatement : public Statement {
 public:
  explicit ReturnStatement(std::unique_ptr<Expression>&& expr)
      : ret_expr_(std::move(expr)) {}
  ~ReturnStatement() override = default;
  llvm::Value* generateCode(DeviantLLVM& context) override;
  std::string toString() override { return "return"; }

 private:
  std::unique_ptr<Expression> ret_expr_;
};

class FunctionStatement : public Statement {
 public:
  FunctionStatement(const std::string& fn_name) : fn_name_(fn_name) {}
  ~FunctionStatement() override = default;
  Type type() override { return Type::STATEMENT; }
  llvm::Value* generateCode(DeviantLLVM& context) override;
  std::string toString() override { return "fn"; }
  Block& getBody() { return body_; }

 private:
  std::string fn_name_;
  Block body_;
};

}  // namespace deviant

#endif  // __AST__
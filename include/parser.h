#ifndef __PARSER_H__
#define __PARSER_H__

#include <map>

#include "ast.h"
#include "lexer.h"
#include "token.h"

namespace deviant {
class Parser {
 public:
  Parser(const std::string& content) : lexer_(content), index_(0) {
    lexer_.tokenize();
  }

  // parse whole program
  std::unique_ptr<Program> parse();

 private:
  // TODO:
  // parsing functions
  std::unique_ptr<Expression> parseExpression();
  std::unique_ptr<Statement> parseTopLevelStatement();
  std::unique_ptr<Statement> parseStatement();
  std::unique_ptr<LetStatement> parseLetStatement();
  std::unique_ptr<FunctionStatement> parseFunctionStatement();
  std::unique_ptr<ReturnStatement> parseReturnStatement();
  std::unique_ptr<Block> parseBlock();
  void parseStringLiteral();
  void parseFunctiot();
  void parseScope();

  [[nodicard]] std::optional<Token> peek(int offset = 0) const;

  const Token& consume();

  Lexer lexer_;

  size_t index_;
};

}  // namespace deviant

#endif

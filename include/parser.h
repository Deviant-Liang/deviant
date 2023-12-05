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
  void parseFunction();
  std::unique_ptr<Statement> parseStatement();
  void parseLetStatement();
  void parseStringLiteral();
  void parseFunctiot();
  void parseBlock();
  void parseScope();

  [[nodicard]] std::optional<Token> peek(int offset) const;

  const Token& consume();

  Lexer lexer_;

  size_t index_;
};

}  // namespace deviant

#endif

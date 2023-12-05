#include "parser.h"

namespace deviant {
std::unique_ptr<Program> Parser::parse() {
  std::unique_ptr<Program> program = std::make_unique<Program>();
  auto statement_ptr = parseStatement();
  if (statement_ptr) {
    program->pushBack(std::move(statement_ptr));
  }
  return program;
}

std::unique_ptr<Statement> Parser::parseStatement() {
  return std::make_unique<Statement>();
}

std::optional<Token> Parser::peek(int offset) const {
  const auto& tokens = lexer_.getTokens();
  if (index_ + offset >= tokens.size())
    return std::nullopt;
  else
    return tokens[index_ + offset];
}

const Token& Parser::consume() {
  return lexer_.getTokens()[index_++];
}
}  // namespace deviant
#include "parser.h"
#include "token.h"

namespace deviant {
std::unique_ptr<Program> Parser::parse() {
  std::unique_ptr<Program> program = std::make_unique<Program>();
  while (index_ < lexer_.getTokens().size()) {
    auto statement_ptr = parseTopLevelStatement();
    if (statement_ptr) {
      program->pushBack(std::move(statement_ptr));
    }
    consume();
  }
  return program;
}

std::unique_ptr<Expression> Parser::parseExpression() {
  if (peek().has_value() && peek().value().value.has_value()) {
    Token token(peek().value());
    const std::string& value(token.value.value());
    if (peek().value().type == TokenType::INT_LIT)
      return std::make_unique<Integer>(stoi(value));
  } else
    return nullptr;
}

std::unique_ptr<Statement> Parser::parseTopLevelStatement() {
  TokenType type =
      peek().has_value() ? peek().value().type : TokenType::ILLEGAL;
  switch (type) {
    case TokenType::FN:
      return parseFunctionStatement();
    default:
      return nullptr;
  }
}

std::unique_ptr<Statement> Parser::parseStatement() {
  TokenType type =
      peek().has_value() ? peek().value().type : TokenType::ILLEGAL;
  switch (type) {
    case TokenType::RETURN:
      return parseReturnStatement();
    default:
      return nullptr;
  }
}

// std::unique_ptr<LetStatement> Parser::parseLetStatement() {}

std::unique_ptr<Block> Parser::parseBlock() {
  auto block = std::make_unique<Block>();

  auto stmt = parseStatement();
  while (stmt) {
    block->insertStatement(std::move(stmt));
    consume();
    stmt = parseStatement();
  }

  return block;
}

std::unique_ptr<ReturnStatement> Parser::parseReturnStatement() {
  consume();
  auto ret_stmt = std::make_unique<ReturnStatement>(parseExpression());

  if (consume().type == TokenType::SEMICOLON)
    return nullptr;

  return ret_stmt;
}

std::unique_ptr<FunctionStatement> Parser::parseFunctionStatement() {
  consume();
  if (peek().value().value.has_value()) {
    auto fn = std::make_unique<FunctionStatement>(peek().value().value.value());

    // TODO: parameters
    consume();
    consume();
    consume();

    if (peek().value().type != TokenType::FN_TYPE)
      return nullptr;

    // TODO: return type
    consume();
    consume();

    if (consume().type == TokenType::OPEN_CURLY) {
      auto& body = fn->getBody();
      auto block = parseBlock();
      auto ptr = block.release();
      // body = *ptr;
    }
    return fn;
  } else {
    return nullptr;
  }
}

std::optional<Token> Parser::peek(const int offset) const {
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
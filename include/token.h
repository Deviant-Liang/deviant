#ifndef __TOKEN_H__
#define __TOKEN_H__

namespace deviant {
enum class TokenType {
  ILLEGAL,
  RETURN,
  INT_LIT,
  INT,
  FN,
  FN_TYPE,
  VAR,
  IF,
  IDENTIFIER,
  OPEN_PAREN,
  CLOSE_PAREN,
  SEMICOLON,
  ASSIGNMENT,
  PLUS,
  MINUS,
  STAR,
  FSLASH,
  LT,
  LE,
  GT,
  GE,
  EQ,
  NEQ,
  EXCLAMATION,
  OPEN_CURLY,
  CLOSE_CURLY
};

struct Token {
  TokenType type;
  std::optional<std::string> value;
};

}  // namespace deviant

#endif  // __TOKEN_H__

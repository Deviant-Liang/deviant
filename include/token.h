#ifndef __TOKEN_H__
#define __TOKEN_H__

namespace deviant {
enum class TokenType {
  RETURN,
  INT_LIT,
  SEMI,
  EXIT,
  LET,
  IF,
  IDENTIFIER,
  OPEN_PAREN,
  CLOSE_PAREN,
  SEMICOLON,
  EQUAL,
  PLUS,
  MINUS,
  STAR,
  FSLASH,
  OPEN_CURLY,
  CLOSE_CURLY
};

struct Token {
  TokenType type;
  std::optional<std::string> value;
};

}  // namespace deviant

#endif  // __TOKEN_H__

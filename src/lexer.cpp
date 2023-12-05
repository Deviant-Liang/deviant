#include "lexer.h"
#include "token.h"

namespace deviant {
Lexer::Lexer(const std::string& src) : index_(0), str_(src) {}

}  // namespace deviant
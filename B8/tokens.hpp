#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <vector>
#include <string>
#include <iostream>

enum TokenTypes {
  WORD,
  WHITESPACE,
  NUMBER,
  PUNCT,
  DASH
};

struct token_t {
  std::string string;
  TokenTypes type;
};

using Token = token_t;
using Tokens = std::vector<Token>;

std::istream& operator>>(std::istream& in, Token& token);
std::vector<std::string> process_tokens(Tokens& tokens, unsigned int width);

#endif //TOKENS_HPP

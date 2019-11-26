#include "tokens.hpp"

#include <stdexcept>
#include <locale>

std::istream& operator>>(std::istream& in, Token& token)
{
  token.string = in.get();
  if (in.eof()) {
    return in;
  }
  if (std::isalpha(token.string.front())) {
    token.type = WORD;
    if (in.peek() == '-') {
      token.string += in.get();
    }
    while (std::isalpha(in.peek())) {
      token.string += in.get();
      if (in.peek() == '-') {
        token.string += in.get();
      }
    }
  } else if (std::isspace(token.string.front())) {
    token.type = WHITESPACE;
    token.string = ' ';
    while (std::isspace(in.peek())) {
      in.get();
    }
  } else if (token.string.front() == '-' || token.string.front() == '+' || std::isdigit(token.string.front())) {
    if (token.string.front() == '-' && in.peek() == '-') {
      token.type = DASH;
      while (in.peek() == '-') {
        token.string += in.get();
      }
    } else {
      token.type = NUMBER;
      bool isFloating = false;
      if (std::isdigit(token.string.front())) {
        if (in.peek() == std::use_facet<std::numpunct<char>>(in.getloc()).decimal_point()) {
          token.string += in.get();
          isFloating = true;
          if (!std::isdigit(in.peek())) {
            token.string.pop_back();
            isFloating = false;
            in.unget();
          }
        }
      }
      while (std::isdigit(in.peek())) {
        token.string += in.get();
        if (!isFloating && in.peek() == std::use_facet<std::numpunct<char>>(in.getloc()).decimal_point()) {
          token.string += in.get();
          isFloating = true;
          if (!std::isdigit(in.peek())) {
            token.string.pop_back();
            isFloating = false;
            in.unget();
          }
        }
      }
    }
  } else if (std::ispunct(token.string.front())) {
    token.type = PUNCT;
  } else {
    throw std::invalid_argument("Invalid character");
  }
  in.clear();
  return in;
}

std::vector<std::string> process_tokens(Tokens& tokens, const unsigned int width)
{
  if (tokens.empty()) {
    return std::vector<std::string>();
  }
  if (tokens.front().type == WHITESPACE) {
    tokens.erase(tokens.begin());
  }
  if (tokens.front().type == PUNCT || tokens.front().type == DASH) {
    throw std::invalid_argument("Text can start only with a word or a number");
  }
  Tokens tempTokens;
  for (size_t i = 0; i < tokens.size(); ++i){
    switch (tokens[i].type) {
      case DASH:
        if (tokens[i].string != "---") {
          throw std::invalid_argument("Invalid dash");
        }
        if (tokens[i - 1].type != WHITESPACE) {
          if (tokens[i - 1].type == PUNCT && tokens[i - 1].string != ",") {
            throw std::invalid_argument("Punctuation marks can't follow each other");
          }
          tempTokens.push_back({" ", WHITESPACE});
        } else if (tokens[i - 2].type == PUNCT && tokens[i - 2].string != ",") {
          throw std::invalid_argument("Punctuation marks can't follow each other");
        }
        tempTokens.push_back(tokens[i]);
        if (i != tokens.size() - 1 && tokens[i + 1].type != WHITESPACE) {
          tempTokens.push_back({" ", WHITESPACE});
        }
        break;
      case PUNCT:
        if (tokens[i - 1].type != WHITESPACE) {
          if (tokens[i - 1].type == PUNCT) {
            throw std::invalid_argument("Punctuation marks can't follow each other");
          }
        } else {
          if (tokens[i - 2].type == PUNCT) {
            throw std::invalid_argument("Punctuation marks can't follow each other");
          }
          tempTokens.pop_back();
        }
        tempTokens.push_back(tokens[i]);
        if (i != tokens.size() - 1 && tokens[i + 1].type != WHITESPACE) {
          tempTokens.push_back({" ", WHITESPACE});
        }
        break;
      case WORD:
      case NUMBER:
        if (tokens[i].string.size() > 20) {
          throw std::invalid_argument("Invalid size");
        }
        if (tokens[i].string == "+" || tokens[i].string == "-") {
          throw std::invalid_argument("Invalid + or -");
        }
        tempTokens.push_back(tokens[i]);
        break;
      case WHITESPACE:
        tempTokens.push_back(tokens[i]);
        break;
    }
  }
  if (tempTokens.empty()) {
    return std::vector<std::string>();
  }
  if (tempTokens.back().type == WHITESPACE) {
    tempTokens.pop_back();
  }

  std::vector<std::string> strings;
  strings.emplace_back();
  for (size_t i = 0; i < tempTokens.size(); ++i) {
    if (strings.back().size() + tempTokens[i].string.size() <= width) {
      strings.back() += tempTokens[i].string;
    } else {
      if (tempTokens[i].type == WHITESPACE) {
        ++i;
      }
      std::string buffer;
      if (tempTokens[i].type == PUNCT || tempTokens[i].type == DASH) {
        size_t j = i;
        do {
          --j;
          strings.back().erase(strings.back().size() - tempTokens[j].string.size());
          buffer.insert(0, tempTokens[j].string);
        } while (tempTokens[j].type == WHITESPACE);
      }
      if (strings.back().back() == ' ') {
        strings.back().pop_back();
      }
      strings.push_back(buffer + tempTokens[i].string);
    }
  }
  return strings;
}

#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "Queue.h"
#include <cstddef>
#include <string>

class Tokenizer {
public:
  static bool isSpace(char);
  static bool isBrace(char);
  static bool isAlpha(char);
  static bool isOperator(char);
  static bool isComma(char);
  static bool isUnderscore(char);
  Tokenizer(const std::string &);
  Tokenizer(const Tokenizer &);
  Queue<std::string> getAllTokens();

private:
  const std::string s;
  std::size_t pos;
  bool hasNextToken() const;
  void skipSpaces();
  std::string getNextToken();
  std::string getNumber();
  std::string getBrace();
  std::string getOperator();
  std::string getComma();
  std::string getName();
  char c() const;
};

#endif

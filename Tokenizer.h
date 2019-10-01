#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "Queue.h"
#include <cstddef>
#include <string>

class Tokenizer {
public:
  Tokenizer(const std::string &);
  Tokenizer(const Tokenizer &);
  Queue<std::string> getAllTokens();

private:
  const std::string s;
  std::size_t pos;
  static bool isSpace(char);
  static bool isDigit(char);
  static bool isBrace(char);
  static bool isAlpha(char);
  static bool isOperator(char);
  bool hasNextToken();
  void skipSpaces();
  std::string getNextToken();
  std::string getNumber();
  std::string getBrace();
  std::string getOperator();
  std::string getName();
};

#endif

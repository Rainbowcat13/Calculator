#include "Tokenizer.h"
#include "Number.h"
#include <stdexcept>

Tokenizer::Tokenizer(const std::string &str) : s(str), pos(0) {}

Tokenizer::Tokenizer(const Tokenizer &t) : s(t.s), pos(0) {}

Queue<std::string> Tokenizer::getAllTokens() {
  Queue<std::string> res;
  pos = 0;
  skipSpaces();
  while (hasNextToken()) {
    res.push(getNextToken());
    skipSpaces();
  }
  return res;
}

bool Tokenizer::isSpace(char c) { return c == ' '; }

bool Tokenizer::isBrace(char c) {
  return c == '(' || c == ')' || c == '[' || c == ']';
}

bool Tokenizer::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Tokenizer::isUnderscore(char c) { return c == '_'; }

bool Tokenizer::isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool Tokenizer::isComma(char c) { return c == ','; }

bool Tokenizer::hasNextToken() const { return pos < s.length(); }

void Tokenizer::skipSpaces() {
  while (isSpace(c()))
    pos++;
}

std::string Tokenizer::getNextToken() {
  if (Number::isDigit(c()))
    return getNumber();
  if (isAlpha(c()))
    return getName();
  if (isBrace(c()))
    return getBrace();
  if (isOperator(c()))
    return getOperator();
  if (isComma(c()))
    return getComma();
  throw std::invalid_argument(std::string("unexpected ") + c());
}

std::string Tokenizer::getNumber() {
  std::size_t n = s.length(), b = pos;
  int dot = -1, exp = -1, sign = -1;
  while (pos < n)
    if (Number::isDot(c()) && pos > b && exp < 0 && dot < 0)
      dot = pos++;
    else if (Number::isExp(c()) && pos > b && exp < 0 && dot != pos - 1)
      exp = pos++;
    else if (Number::isSign(c()) && (exp == pos - 1 || b == pos))
      sign = pos++;
    else if (Number::isDigit(c()))
      pos++;
    else
      break;
  if (dot == pos - 1 || exp == pos - 1 || sign == pos - 1)
    throw std::invalid_argument(std::string("unexpected ") + c());
  return s.substr(b, pos - b);
}

std::string Tokenizer::getBrace() {
  if (!isBrace(c()))
    throw std::invalid_argument(std::string("unexpected ") + c());
  return s.substr(pos++, 1);
}

std::string Tokenizer::getOperator() {
  if (!isOperator(c()))
    throw std::invalid_argument(std::string("unexpected ") + c());
  return s.substr(pos++, 1);
}

std::string Tokenizer::getComma() {
  if (!isComma(c()))
    throw std::invalid_argument(std::string("unexpected ") + c());
  return s.substr(pos++, 1);
}

std::string Tokenizer::getName() {
  std::size_t n = s.length(), b = pos;
  if (!isAlpha(c()))
    throw std::invalid_argument(std::string("unexpected ") + c());
  while (pos < n && (isAlpha(c()) || Number::isDigit(c()) || isUnderscore(c())))
    pos++;
  return s.substr(b, pos - b);
}

char Tokenizer::c() const { return s[pos]; }

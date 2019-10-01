#include "Tokenizer.h"
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

bool Tokenizer::isDigit(char c) { return c >= '0' && c <= '9'; }

bool Tokenizer::isBrace(char c) {
  return c == '(' || c == ')' || c == '[' || c == ']';
}

bool Tokenizer::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Tokenizer::isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool Tokenizer::hasNextToken() { return pos < s.length(); }

void Tokenizer::skipSpaces() {
  while (isSpace(s[pos]))
    pos++;
}

std::string Tokenizer::getNextToken() {
  if (isDigit(s[pos]))
    return getNumber();
  if (isAlpha(s[pos]))
    return getName();
  if (isBrace(s[pos]))
    return getBrace();
  if (isOperator(s[pos]))
    return getOperator();
  throw std::invalid_argument("unexpected " + s[pos]);
}

std::string Tokenizer::getNumber() {
  std::size_t b = pos;
  if (!isDigit(s[b]))
    return "";
  for (; isDigit(s[pos]) || s[pos] == '.' || s[pos] == 'e'; pos++) {
  }
  return s.substr(b, pos - b);
}

std::string Tokenizer::getBrace() {
  if (!isBrace(s[pos]))
    return "";
  return s.substr(pos++, 1);
}

std::string Tokenizer::getOperator() {
  if (!isOperator(s[pos]))
    return "";
  return s.substr(pos++, 1);
}

std::string Tokenizer::getName() {
  std::size_t b = pos;
  if (!isAlpha(s[b]))
    return "";
  for (; isAlpha(s[pos]) || s[pos] == '_'; pos++) {
  }
  return s.substr(b, pos - b);
}

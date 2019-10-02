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
  if (s[pos] == ',')
    return s.substr(pos++, 1);
  throw std::invalid_argument(std::string("unexpected ") + s[pos]);
}

std::string Tokenizer::getNumber() {
  std::size_t b = pos;
  int n = s.length(), dot = -2, exp = -2;
  while (pos < n)
    if (s[pos] == '.' && pos > b && exp < 0 && dot < 0)
      dot = pos++;
    else if (s[pos] == 'e' && pos > b && exp < 0 && dot != pos - 1)
      exp = pos++;
    else if ((s[pos] == '-' || s[pos] == '+') && (exp == pos - 1 || b == pos))
      pos++;
    else if (s[pos] >= '0' && s[pos] <= '9')
      pos++;
    else
      break;
  if (dot == pos - 1 || exp == pos - 1)
    throw std::invalid_argument(std::string("no digit after ") + s[pos - 1]);
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

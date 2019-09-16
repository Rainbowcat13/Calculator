#ifndef STRING_H
#define STRING_H

class String {
  public:
    String() {}
    String(const char *);
    String(const String &);
    unsigned int size();
    bool isEmpty();
    bool operator==(const char *);
    bool operator==(const String &);
    char operator[](unsigned int);
  private:
    unsigned int sz = 0;
    char *ptr = nullptr;
};

#endif


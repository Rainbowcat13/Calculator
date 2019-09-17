#ifndef STRING_H
#define STRING_H

class String {
  public:
    String() {}
    String(const char *);
    String(const String &);
    unsigned int size() const;
    bool isEmpty() const;
    bool operator==(const char *) const;
    bool operator==(const String &) const;
    char operator[](unsigned int) const;
  private:
    unsigned int sz = 0;
    char *ptr = nullptr;
};

#endif


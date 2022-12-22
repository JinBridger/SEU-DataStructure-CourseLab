#pragma once

#include <iostream>

/**
 *  @class   MyStr
 *  @brief   own-made string class, support some basic operations.
 *  @details ~
 */
class MyStr {
    friend std::istream& operator>>(std::istream&, MyStr&);
    friend std::ostream& operator<<(std::ostream&, const MyStr&);

    friend MyStr operator+(const MyStr&, const MyStr&);

    friend bool operator==(const MyStr&, const MyStr&);
    friend bool operator<(const MyStr&, const MyStr&);
    friend bool operator>(const MyStr&, const MyStr&);

public:
    MyStr();
    MyStr(const char*);
    MyStr(const MyStr&);
    ~MyStr();

    char& operator[](int);

    MyStr substr(int, int) const;
    int   length() const;

private:
    int   m_length;
    char* m_str;
};
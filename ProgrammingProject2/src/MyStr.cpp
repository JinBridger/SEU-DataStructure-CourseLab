/**
 *  @file      MyStr.cpp
 *  @brief     MyStr class
 *  @details   ~
 *  @author    JinBridge
 *  @date      21.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */

#include "MyStr.h"

/**
 *  @brief MyStr object constructor
 */
MyStr::MyStr() : m_length(0) {
    m_str    = new char[1];
    m_str[0] = '\0';
}

/**
 *  @brief MyStr object constructor
 *  @param c - string constant. eg. "str"
 */
MyStr::MyStr(const char* c) : m_length(0) {
    const char* it = c;
    while (*it != '\0') {
        it++;
        m_length++;
    }
    m_str = new char[m_length + 1];
    for (int i = 0; c[i] != '\0'; ++i) {
        m_str[i] = c[i];
    }
    m_str[m_length] = '\0';
}

/**
 *  @brief MyStr copy constructor
 *  @param s - copy string
 */
MyStr::MyStr(const MyStr& s) : m_length(s.m_length) {
    m_str = new char[m_length + 1];
    for (int i = 0; i <= m_length; ++i) {
        m_str[i] = s.m_str[i];
    }
}

/**
 *  @brief MyStr object destructor
 */
MyStr::~MyStr() {
    if (!m_str)
        delete[] m_str;
}

/**
 *  @brief  get substring from [start, start + offset)
 *  @param  start  - start position
 *  @param  offset - substring length
 *  @retval        - substring
 */
MyStr MyStr::substr(int start, int offset) const {
    MyStr ret;
    ret.m_length = offset;
    delete[] ret.m_str;
    ret.m_str = new char[ret.m_length + 1];
    for (int i = start; i < start + offset; ++i) {
        ret.m_str[i - start] = m_str[i];
    }
    ret.m_str[ret.m_length] = '\0';
    return ret;
}

std::istream& operator>>(std::istream& is, MyStr& s) {
    s.m_length = 0;
    delete[] s.m_str;

    char* temp = new char[1000];
    is >> temp;
    for (int i = 0; temp[i] != '\0'; ++i) {
        s.m_length++;
    }
    s.m_str = new char[s.m_length + 1];
    for (int i = 0; temp[i] != '\0'; ++i) {
        s.m_str[i] = temp[i];
    }
    s.m_str[s.m_length] = '\0';
    return is;
}

std::ostream& operator<<(std::ostream& os, const MyStr& s) {
    os << s.m_str;
    return os;
}

MyStr operator+(const MyStr& a, const MyStr& b) {
    MyStr ret;
    ret.m_length = a.m_length + b.m_length;
    delete[] ret.m_str;
    ret.m_str = new char[ret.m_length + 1];
    for (int i = 0; i < a.m_length; ++i) {
        ret.m_str[i] = a.m_str[i];
    }
    for (int j = 0; j < b.m_length; ++j) {
        if (j + a.m_length < ret.m_length)
            ret.m_str[j + a.m_length] = b.m_str[j];
    }
    ret.m_str[ret.m_length] = '\0';
    return ret;
}

bool operator==(const MyStr& a, const MyStr& b) {
    if (a.m_length != b.m_length)
        return false;
    for (int i = 0; i < a.m_length; ++i)
        if (a.m_str[i] != b.m_str[i])
            return false;
    return true;
}

bool operator<(const MyStr& a, const MyStr& b) {
    int minLen = (a.m_length < b.m_length) ? a.m_length : b.m_length;
    for (int i = 0; i < minLen; ++i) {
        if (a.m_str[i] != b.m_str[i])
            return a.m_str[i] < b.m_str[i];
    }
    return minLen == a.m_length;
}

bool operator>(const MyStr& a, const MyStr& b) {
    return !(a == b) && !(a < b);
}

char& MyStr::operator[](int n) {
    if (n >= m_length) {
        throw("Out of range!");
    }
    return m_str[n];
}

/**
 *  @brief  get length
 *  @retval int - length
 */
int MyStr::length() const {
    return m_length;
}
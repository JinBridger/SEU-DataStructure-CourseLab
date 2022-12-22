#include "SeqList.h"

#include <iostream>

template <typename T>
SeqList<T>::SeqList(int len, T* dataPtr) : m_length(len) {
    m_dataPtr = new T[len];
    for (int i = 0; i < len; ++i) {
        m_dataPtr[i] = dataPtr[i];
    }
}

template <typename T>
SeqList<T>::SeqList(int len) : m_length(len) {
    m_dataPtr = new T[len];
}

template <typename T>
int SeqList<T>::length() {
    return m_length;
}

template <typename T>
T SeqList<T>::retrieve(int index) {
    if (index >= m_length || index < 0) {
        std::cout << "Invaild index!" << std::endl;
        exit(0);
    }
    return m_dataPtr[index];
}

template <typename T>
void SeqList<T>::store(int index, T data) {
    if (index >= m_length || index < 0) {
        std::cout << "Invaild index!" << std::endl;
        exit(0);
    }
    m_dataPtr[index] = data;
}

template <typename T>
void SeqList<T>::insert(int index, T data) {
    if (index >= m_length || index < 0) {
        std::cout << "Invaild index!" << std::endl;
        exit(0);
    }
    T* tempPtr = new T[m_length + 1];
    for (int i = 0; i < index; ++i) {
        tempPtr[i] = m_dataPtr[i];
    }
    tempPtr[index] = data;
    for (int i = index + 1; i <= m_length; ++i) {
        tempPtr[i] = m_dataPtr[i - 1];
    }
    m_length++;
    delete[] m_dataPtr;
    m_dataPtr = new T[m_length];
    for (int i = 0; i < m_length; ++i) {
        m_dataPtr[i] = tempPtr[i];
    }
    delete[] tempPtr;
}

template <typename T>
T SeqList<T>::remove(int index) {
    if (index >= m_length || index < 0) {
        std::cout << "Invaild index!" << std::endl;
        exit(0);
    }
    T  ret     = m_dataPtr[index];
    T* tempPtr = new T[m_length - 1];
    for (int i = 0; i < index; ++i) {
        tempPtr[i] = m_dataPtr[i];
    }
    for (int i = index + 1; i < m_length; ++i) {
        tempPtr[i - 1] = m_dataPtr[i];
    }
    m_length--;
    delete[] m_dataPtr;
    m_dataPtr = new T[m_length];
    for (int i = 0; i < m_length; ++i) {
        m_dataPtr[i] = tempPtr[i];
    }
    delete[] tempPtr;
    return ret;
}

template <typename T>
void SeqList<T>::print() {
    for (int i = 0; i < m_length - 1; ++i) {
        std::cout << m_dataPtr[i] << ", ";
    }
    std::cout << m_dataPtr[m_length - 1] << std::endl;
}

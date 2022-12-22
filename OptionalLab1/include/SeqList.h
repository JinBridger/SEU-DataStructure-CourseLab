#pragma once

template <typename T>
class SeqList {
public:
    SeqList(int len, T* dataPtr);
    SeqList(int len);
    SeqList() = default;

    int  length();
    T    retrieve(int index);
    void store(int index, T data);
    void insert(int index, T data);
    T    remove(int index);

    void print();

private:
    int m_length;
    T*  m_dataPtr;
};

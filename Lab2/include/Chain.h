/**
 *  @file      Chain.h
 *  @brief     Chain Class
 *  @details   ~
 *  @author    JinBridge
 *  @date      11.10.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once
#include "ChainNode.h"

#include <iostream>

/**
 *  @class   Chain
 *  @brief   The Chain
 *  @details ~
 *  @tparam  dataType - The type of data
 */
template <typename dataType>
class Chain {
public:
    dataType        operator[](int);
    const dataType& operator[](int) const;

    Chain();
    ~Chain();

    bool isEmpty() const;

    void insertFirst(const dataType&);
    void insertIndex(int, const dataType&);
    void insertLast(const dataType&);

    void deleteFirst();
    void deleteIndex(int);
    void deleteLast();

    int  size() const;
    void print() const;

    ChainNode<dataType>* m_first;

private:
    int m_size;
};

/**
 *  @brief  Return n-th element in chain
 *  @param  n - index
 *  @retval dataType - element's value
 */
template <typename dataType>
dataType Chain<dataType>::operator[](int n) {
    if (n > m_size - 1 || n < 0) {
        std::cout << "Invalid index!" << std::endl;
        exit(0);
    }
    ChainNode<dataType>* retPtr = m_first;
    for (int i = 0; i < n; ++i) {
        retPtr = retPtr->m_link;
    }
    return retPtr->m_data;
}

/**
 *  @brief  Return const& n-th element in chain
 *  @param  n - index
 *  @retval const dataType& - element's value
 */
template <typename dataType>
const dataType& Chain<dataType>::operator[](int n) const {
    if (n > m_size - 1 || n < 0) {
        std::cout << "Invalid index!" << std::endl;
        exit(0);
    }
    ChainNode<dataType>* retPtr = m_first;
    for (int i = 0; i < n; ++i) {
        retPtr = retPtr->m_link;
    }
    return retPtr->m_data;
}

/**
 *  @brief Chain object constructor
 */
template <typename dataType>
Chain<dataType>::Chain() {
    m_first = nullptr;
    m_size  = 0;
}

/**
 *  @brief Chain object destructor
 */
template <typename dataType>
Chain<dataType>::~Chain() {
    while (m_first != nullptr) {
        ChainNode<dataType>* nextNode = m_first->m_link;
        delete m_first;
        m_first = nextNode;
    }
}

/**
 *  @brief  Return whether the Chain is empty
 *  @retval bool - Whether the Chain is empty
 */
template <typename dataType>
bool Chain<dataType>::isEmpty() const {
    return m_size == 0;
}

/**
 *  @brief Insert an element at the first of Chain
 *  @param data - the data to be inserted
 */
template <typename dataType>
void Chain<dataType>::insertFirst(const dataType& data) {
    ChainNode<dataType>* newFirst = new ChainNode<dataType>(data, m_first);
    m_first                       = newFirst;
    m_size++;
}

/**
 *  @brief Insert an element at the given index
 *  @param index - the place to insert
 *  @param data - the data to be inserted
 */
template <typename dataType>
void Chain<dataType>::insertIndex(int index, const dataType& data) {
    if (index <= 0 || index >= m_size) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    ChainNode<dataType>* insertPtr = m_first;
    for (int i = 0; i < index - 1; ++i) {
        insertPtr = insertPtr->m_link;
    }
    ChainNode<dataType>* tempPtr = insertPtr->m_link;
    insertPtr->m_link            = new ChainNode<dataType>(data, tempPtr);
    m_size++;
}

/**
 *  @brief Insert an element at the last of Chain
 *  @param data - the data to be inserted
 */
template <typename dataType>
void Chain<dataType>::insertLast(const dataType& data) {
    ChainNode<dataType>* insertPtr = m_first;
    while (insertPtr->m_link != nullptr) {
        insertPtr = insertPtr->m_link;
    }
    insertPtr->m_link = new ChainNode<dataType>(data, nullptr);
    m_size++;
}

/**
 *  @brief Delete the first data in the chain
 */
template <typename dataType>
void Chain<dataType>::deleteFirst() {
    if (m_size == 0) {
        std::cout << "Cannot delete the first element of an empty chain!" << std::endl;
        return;
    }
    if (m_size == 1) {
        delete m_first;
        m_first = nullptr;
        m_size--;
        return;
    }
    ChainNode<dataType>* tempPtr = m_first->m_link;
    delete m_first;
    m_first = tempPtr;
    m_size--;
}

/**
 *  @brief Delete the data of the index
 *  @param index - The index of the data to be deleted
 */
template <typename dataType>
void Chain<dataType>::deleteIndex(int index) {
    if (index <= 0 || index >= m_size - 1) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    ChainNode<dataType>* deletePtr = m_first;
    for (int i = 0; i < index - 1; ++i) {
        deletePtr = deletePtr->m_link;
    }
    ChainNode<dataType>* tempPtr = (deletePtr->m_link)->m_link;
    delete (deletePtr->m_link);
    deletePtr->m_link = tempPtr;
    m_size--;
}

/**
 *  @brief Delete the last data in the chain
 */
template <typename dataType>
void Chain<dataType>::deleteLast() {
    if (m_size == 0) {
        std::cout << "Cannot delete the last element of an empty chain!" << std::endl;
        return;
    }
    if (m_size == 1) {
        delete m_first;
        m_first = nullptr;
        m_size--;
        return;
    }
    ChainNode<dataType>* deletePtr = m_first;
    while ((deletePtr->m_link)->m_link != nullptr) {
        deletePtr = deletePtr->m_link;
    }
    delete deletePtr->m_link;
    deletePtr->m_link = nullptr;
    m_size--;
}

/**
 *  @brief  Return the size of the chain
 *  @retval size - the size of the chain
 */
template <typename dataType>
int Chain<dataType>::size() const {
    return m_size;
}

/**
 *  @brief Print the Chain
 */
template <typename dataType>
void Chain<dataType>::print() const {
    ChainNode<dataType>* printPtr = m_first;
    while (printPtr != nullptr) {
        std::cout << printPtr->m_data << " ";
        printPtr = printPtr->m_link;
    }
    std::cout << std::endl;
}

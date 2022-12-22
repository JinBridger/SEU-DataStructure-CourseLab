/**
 *  @file      MinHeap.hpp
 *  @brief     MinHeap template class
 *  @details   ~
 *  @author    JinBridge
 *  @date      23.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once
#include <iostream>

/**
 *  @class   MinHeap
 *  @brief   minimal heap template class
 *  @details ~
 *  @tparam  DataType - type of data
 */
template <typename DataType>
class MinHeap {
public:
    /**
     *  @brief MinHeap object constructor
     *  @param size - array size
     *  @param arr  - array data
     */
    MinHeap(int size = 0, DataType* arr = nullptr) : m_size(size) {
        m_data    = new DataType[size + 1];
        m_data[0] = 0;

        if (arr != nullptr) {
            for (int i = 0; i < size; ++i) {
                m_data[i + 1] = arr[i];
            }
            for (int i = 1; i <= m_size; ++i)
                shiftUp(i);
        }
    }

    /**
     *  @brief MinHeap object destructor
     */
    ~MinHeap() {
        delete[] m_data;
    }

    /**
     *  @brief  get the top element
     *  @retval  - top element
     */
    DataType top() const {
        return m_data[1];
    }

    /**
     *  @brief  pop the top element
     *  @retval  - top element before popping
     */
    DataType pop() {
        if (m_size == 0)
            throw("Couldn't pop an empty heap!");

        DataType ret   = m_data[1];
        DataType tmp   = m_data[1];
        m_data[1]      = m_data[m_size];
        m_data[m_size] = tmp;

        DataType* newData = new DataType[m_size];
        for (int i = 0; i < m_size; ++i) {
            newData[i] = m_data[i];
        }
        m_size--;
        delete[] m_data;
        m_data = newData;
        shiftDown(1);

        return ret;
    }

    /**
     *  @brief insert an element
     *  @param data - insert data
     */
    void insert(const DataType& data) {
        DataType* tmp = new DataType[m_size + 2];
        for (int i = 0; i <= m_size; ++i) {
            tmp[i] = m_data[i];
        }
        tmp[++m_size] = data;
        delete[] m_data;
        m_data = tmp;
        shiftUp(m_size);
    }

    /**
     *  @brief print all elements
     */
    void print() const {
        for (int i = 1; i <= m_size; i++)
            std::cout << m_data[i] << std::endl;
    }

    /**
     *  @brief  return if the heap is empty
     *  @retval  - true when heap is empty
     */
    bool empty() const {
        return m_size == 0;
    }

    /**
     *  @brief  return the size of heap
     *  @retval  - size of heap
     */
    int size() const {
        return m_size;
    }

private:
    /**
     *  @brief move an element upper
     *  @param pos - the index of moving element
     */
    void shiftUp(int pos) {
        while (pos > 1 && m_data[pos] < m_data[pos / 2]) {
            DataType tmp    = m_data[pos];
            m_data[pos]     = m_data[pos / 2];
            m_data[pos / 2] = tmp;
            pos /= 2;
        }
    }

    /**
     *  @brief move an element lower
     *  @param pos - the index of moving element
     */
    void shiftDown(int pos) {
        while (pos * 2 <= m_size) {
            int tmpPos = pos * 2;
            if (tmpPos + 1 <= m_size && m_data[tmpPos + 1] < m_data[tmpPos]) {
                tmpPos++;
            }
            if (m_data[tmpPos] >= m_data[pos]) {
                break;
            }

            DataType tmp   = m_data[pos];
            m_data[pos]    = m_data[tmpPos];
            m_data[tmpPos] = tmp;
            pos            = tmpPos;
        }
    }

    DataType* m_data;
    int       m_size;
};
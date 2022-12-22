#pragma once

/**
 *  @class   MyVec
 *  @brief   own-made vector class, support some basic operations.
 *  @details ~
 *  @tparam  DT - data type
 */
template <typename DT>
class MyVec {
public:
    /**
     *  @brief MyVec object constructor
     */
    MyVec() : m_size(0), m_begin(nullptr) {}

    /**
     *  @brief MyVec object constructor, copy from begin to end
     *  @param begin - begin position
     *  @param end   - end position
     */
    MyVec(DT* begin, DT* end) : m_size(int(end - begin)) {
        m_begin = new DT[m_size];
        for (int i = 0; i < m_size; ++i) {
            m_begin[i] = begin[i];
        }
    }

    /**
     *  @brief MyVec object copy constructor
     *  @param vec - copy vector
     */
    MyVec(const MyVec<DT>& vec) {
        auto vecBegin = vec.begin();
        auto vecEnd   = vec.end();

        m_size = int(vecEnd - vecBegin);

        m_begin = new DT[m_size];
        for (int i = 0; i < m_size; ++i) {
            m_begin[i] = vecBegin[i];
        }
    }

    /**
     *  @brief MyVec object destructor
     */
    ~MyVec() {
        delete[] m_begin;
    }

    DT& operator[](int n) {
        if (n >= m_size) {
            throw("Out of range!");
        }
        if (!m_begin) {
            throw("Vector is empty!");
        }
        return m_begin[n];
    }

    /**
     *  @brief push element to the end of vector
     *  @param element - data to be pushed
     */
    void pushBack(const DT& element) {
        DT* tmpPtr = new DT[m_size + 1];

        for (int i = 0; i < m_size; ++i)
            tmpPtr[i] = m_begin[i];
        tmpPtr[m_size] = element;

        delete[] m_begin;
        m_size++;
        m_begin = tmpPtr;
    }

    /**
     *  @brief bubble sort
     *  @param fun - sort order
     */
    void sort(bool(*fun)(DT, DT)) {
        for (int i = 0; i < m_size - 1; ++i) {
            for (int j = 0; j < m_size - 1 - i; ++j) {
                if (fun(m_begin[j], m_begin[j + 1])) {
                    DT tmp = m_begin[j];
                    m_begin[j] = m_begin[j + 1];
                    m_begin[j + 1] = tmp;
                }
            }
        }
    }

    /**
     *  @brief  Return iterator to beginning
     *  @retval  - iterator to beginning
     */
    DT* begin() const {
        return m_begin;
    }

    /**
     *  @brief  Return iterator to end
     *  @retval  - iterator to end
     */
    DT* end() const {
        return m_begin + m_size;
    }

    /**
     *  @brief  Return size
     *  @retval  - size of vector
     */
    int size() const {
        return m_size;
    }

private:
    int m_size;
    DT* m_begin;
};
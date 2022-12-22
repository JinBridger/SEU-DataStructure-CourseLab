#include "SeqList.cpp"

#include <iostream>

// Return modified list
template <typename T>
SeqList<T> moveZeros(SeqList<T> list) {
    SeqList<T> ret(list.length());
    int        retIndex = 0;
    for (int i = 0; i < list.length(); ++i) {
        if (list.retrieve(i) != ( T )0) {
            ret.store(retIndex, list.retrieve(i));
            ++retIndex;
        }
    }
    for (; retIndex < list.length(); ++retIndex) {
        ret.store(retIndex, ( T )0);
    }
    return ret;
}

int main() {
    int          data[] = { 1, 7, 5, 2, 0, 3, 4, 0, 6, 9 };
    SeqList<int> test(10, data);

    std::cout << "Before modified: " << std::endl;
    test.print();

    std::cout << "After modified: " << std::endl;
    moveZeros(test).print();
}
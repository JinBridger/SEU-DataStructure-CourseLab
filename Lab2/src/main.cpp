/**
 *  @file      main.cpp
 *  @brief     Main Function
 *  @details   ~
 *  @author    JinBridge
 *  @date      11.10.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#include "Chain.h"
#include "ChainNode.h"
#include "Ex6.h"

#include <iostream>

int main() {
    Chain<char> testChain;
    testChain.insertFirst('g');
    testChain.insertFirst('f');
    testChain.insertFirst('e');
    testChain.insertFirst('d');
    testChain.insertFirst('c');
    testChain.insertFirst('b');
    testChain.insertFirst('a');

    std::cout << "This is the original chain:" << std::endl;
    testChain.print();

    std::cout << "Now delete the element which index is 2:" << std::endl;
    testChain.deleteIndex(2);
    testChain.print();

    std::cout << "Now delete the first element:" << std::endl;
    testChain.deleteFirst();
    testChain.print();

    std::cout << "Now delete the last element:" << std::endl;
    testChain.deleteLast();
    testChain.print();

    std::cout << "Now insert 'a' as the first element:" << std::endl;
    testChain.insertFirst('a');
    testChain.print();

    std::cout << "Now insert 'c' as the element which index is 2:" << std::endl;
    testChain.insertIndex(2, 'c');
    testChain.print();

    std::cout << "Now insert 'g' as the last element:" << std::endl;
    testChain.insertLast('g');
    testChain.print();

    std::cout << std::endl;

    std::cout << "Ex6:" << std::endl;
    std::cout << "Original Chain:" << std::endl;

    Chain<char> leftChain;
    leftChain.insertFirst('a');
    leftChain.insertFirst('b');
    leftChain.insertFirst('c');

    Chain<char> rightChain;
    rightChain.insertFirst('f');
    rightChain.insertFirst('e');
    rightChain.insertFirst('d');

    std::cout << "    l r" << std::endl;
    std::cout << "    | |" << std::endl;
    for (int i = leftChain.size() - 1; i >= 0; --i) {
        std::cout << leftChain[i] << " ";
    }
    rightChain.print();

    moveLeft(leftChain.m_first, rightChain.m_first, 1);

    std::cout << "Now move 1 left:" << std::endl;
    std::cout << "  l r" << std::endl;
    std::cout << "  | |" << std::endl;
    for (int i = leftChain.size() - 2; i >= 0; --i) {
        std::cout << leftChain[i] << " ";
    }
    rightChain.print();

    moveRight(leftChain.m_first, rightChain.m_first, 1);

    std::cout << "Now move 2 right:" << std::endl;
    std::cout << "      l r" << std::endl;
    std::cout << "      | |" << std::endl;
    for (int i = leftChain.size() - 1; i >= 0; --i) {
        std::cout << leftChain[i] << " ";
    }
    rightChain.print();

    return 0;
}
/**
 *  @file      main.cpp
 *  @brief     main function
 *  @details   ~
 *  @author    JinBridge
 *  @date      30.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#include "AVLTree.hpp"

#include <fstream>
#include <iostream>
#include <string>

/**
 *  @brief  insert with printing out the tree
 *  @tparam T    - datatype
 *  @param  tree -
 *  @param  val  -
 */
template <typename T>
void insertTree(AVLTree<T>& tree, const T& val) {
    std::cout << "Insert " << val << ":" << std::endl;
    tree.insert(val);
    tree.print();
    std::cout << std::endl;
}

/**
 *  @brief  remove with printing out the tree
 *  @tparam T    - datatype
 *  @param  tree -
 *  @param  val  -
 */
template <typename T>
void removeTree(AVLTree<T>& tree, const T& val) {
    std::cout << "Remove " << val << ":" << std::endl;
    tree.remove(val);
    tree.print();
    std::cout << std::endl;
}

int main() {
    std::ifstream is("./res/input1.txt");

    int num;
    is >> num;
    std::string* input = new std::string[num];
    for (int i = 0; i < num; ++i) {
        is >> input[i];
    }

    AVLTree<std::string> test;

    for (int i = 0; i < num; ++i) {
        insertTree(test, input[i]);
    }

    for (int i = num - 1; i >= 0; --i) {
        removeTree(test, input[i]);
    }

    return 0;
}
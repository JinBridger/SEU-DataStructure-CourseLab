/**
 *  @file      main.cpp
 *  @brief     main function
 *  @details   ~
 *  @author    JinBridge
 *  @date      25.10.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */

#include "BinaryTree.hpp"

#include <Windows.h>
#include <iostream>

int main() {
    int             treeData[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    BinaryTree<int> tree(treeData, 7);

    system("chcp 65001 && cls");
    std::cout << "Before swapping:" << std::endl;
    tree.print();

    tree.swapTree();
    std::cout << std::endl;
    std::cout << "After swapping:" << std::endl;
    tree.print();
}
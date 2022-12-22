/**
 *  @file      main.cpp
 *  @brief     Main Function
 *  @details   ~
 *  @author    JinBridge
 *  @date      2.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */

#include "BinarySearchTree.hpp"
#include "BinaryTree.hpp"

#include <Windows.h>
#include <iostream>

int main() {
    // Switch to unicode to show some character
    system("chcp 65001 && cls");

    std::cout << "Now read from file..." << std::endl;
    auto is = std::ifstream("res\\input.txt", std::ios_base::in);
    BinarySearchTree<int, int> t(&is);
    std::cout << "Tree read from file: " << std::endl;
    t.print();
    std::cout << "Height now: \t" << t.height() << std::endl;
    std::cout << "Size now: \t" << t.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Now insert (2, 2)..." << std::endl;
    t.insert(2, 2);
    t.print();
    std::cout << "Height now: \t" << t.height() << std::endl;
    std::cout << "Size now: \t" << t.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Now remove node whose key is 6..." << std::endl;
    t.remove(6);
    t.print();
    std::cout << "Height now: \t" << t.height() << std::endl;
    std::cout << "Size now: \t" << t.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Now let's see if key 4 is in the tree..." << std::endl;
    if (t.search(4)) {
        std::cout << "Key 4 is in the tree!" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Now make the tree empty..." << std::endl;
    t.makeEmpty();
    t.print();
    std::cout << "Height now: \t" << t.height() << std::endl;
    std::cout << "Size now: \t" << t.size() << std::endl;
}
/**
 *  @file      BinaryTree.hpp
 *  @brief     Binary Tree Class
 *  @details   ~
 *  @author    JinBridge
 *  @date      25.10.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once
#include "BinaryTreeNode.hpp"

#include <iostream>
#include <string>

/**
 *  @class   BinaryTree
 *  @brief   Binary Tree Class
 *  @details ~
 *  @tparam  dataType - Type of data
 */
template <typename dataType>
class BinaryTree {
public:
    BinaryTree(dataType*, int);
    //    BinaryTree(const BinaryTree<dataType>&);
    ~BinaryTree();

    void print() const;
    void swapTree();

private:
    BinaryTreeNode<dataType>* constructRecursion(dataType*, int, int);
    void                      destructionRecursion(BinaryTreeNode<dataType>*);
    void                      printRecursion(std::string, BinaryTreeNode<dataType>*, bool) const;
    void                      swapTreeRecursion(BinaryTreeNode<dataType>*);

    BinaryTreeNode<dataType>* m_root;
};

/**
 *  @brief BinaryTree object constructor
 *  @param data - Data array with length of len + 1
 *  @param len - Length of data array
 */
template <typename dataType>
BinaryTree<dataType>::BinaryTree(dataType* data, int len) {
    m_root = constructRecursion(data, len, 1);
}

/**
 *  @brief BinaryTree object destructor
 */
template <typename dataType>
BinaryTree<dataType>::~BinaryTree() {
    destructionRecursion(m_root);
}

/**
 *  @brief Print the binary tree
 */
template <typename dataType>
void BinaryTree<dataType>::print() const {
    printRecursion("", m_root, false);
}

/**
 *  @brief Swap tree
 */
template <typename dataType>
void BinaryTree<dataType>::swapTree() {
    swapTreeRecursion(m_root);
}

/**
 *  @brief  Recursion construction function
 *  @param  dataArray - Data array
 *  @param  len - Length of data array
 *  @param  num - No. of current constructing node
 *  @retval BinaryTreeNode<dataType>* - Pointer to the constructing node
 */
template <typename dataType>
BinaryTreeNode<dataType>* BinaryTree<dataType>::constructRecursion(dataType* dataArray, int len,
                                                                   int num) {
    if (num > len || !dataArray[num]) {
        return nullptr;
    }
    BinaryTreeNode<dataType>* retPtr = new BinaryTreeNode<dataType>(dataArray[num]);

    retPtr->m_leftChild  = constructRecursion(dataArray, len, num * 2);
    retPtr->m_rightChild = constructRecursion(dataArray, len, num * 2 + 1);

    return retPtr;
}

/**
 *  @brief Recursion destruction function
 *  @param node - Current destructing node
 */
template <typename dataType>
void BinaryTree<dataType>::destructionRecursion(BinaryTreeNode<dataType>* node) {
    if (node == nullptr)
        return;
    destructionRecursion(node->m_leftChild);
    destructionRecursion(node->m_rightChild);
    delete node;
}

/**
 *  @brief Recursion print function
 *  @param prefix - Prefix string
 *  @param node - Current node
 *  @param isLeft - Is left child
 */
template <typename dataType>
void BinaryTree<dataType>::printRecursion(std::string prefix, BinaryTreeNode<dataType>* node,
                                          bool isLeft) const {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");
        std::cout << node->m_data << std::endl;

        printRecursion(prefix + (isLeft ? "|   " : "    "), node->m_leftChild, true);
        printRecursion(prefix + (isLeft ? "|   " : "    "), node->m_rightChild, false);
    }
}

/**
 *  @brief Recursion swap tree function
 *  @param node - Current swapping node
 */
template <typename dataType>
void BinaryTree<dataType>::swapTreeRecursion(BinaryTreeNode<dataType>* node) {
    if (node == nullptr)
        return;
    swapTreeRecursion(node->m_leftChild);
    swapTreeRecursion(node->m_rightChild);

    BinaryTreeNode<dataType>* tmpPtr = node->m_leftChild;
    node->m_leftChild                = node->m_rightChild;
    node->m_rightChild               = tmpPtr;
}

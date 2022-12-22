/**
 *  @file      BinaryTreeNode.hpp
 *  @brief     Binary Tree Node
 *  @details   ~
 *  @author    JinBridge
 *  @date      25.10.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once

template <typename dataType>
class BinaryTree;

/**
 *  @class   BinaryTreeNode
 *  @brief   Binary Tree Node Class
 *  @details ~
 *  @tparam  dataType - Type of data
 */
template <typename dataType>
class BinaryTreeNode {
    friend class BinaryTree<dataType>;

public:
    BinaryTreeNode(dataType);
    BinaryTreeNode(dataType, BinaryTreeNode<dataType>*, BinaryTreeNode<dataType>*);
    ~BinaryTreeNode();

private:
    dataType                  m_data;
    BinaryTreeNode<dataType>* m_leftChild;
    BinaryTreeNode<dataType>* m_rightChild;
};

/**
 *  @brief BinaryTreeNode object constructor
 *  @param data - Data of the node
 */
template <typename dataType>
BinaryTreeNode<dataType>::BinaryTreeNode(dataType data)
    : m_data(data), m_leftChild(nullptr), m_rightChild(nullptr) {}

/**
 *  @brief BinaryTreeNode object constructor
 *  @param data - Data of the node
 *  @param leftChild - Pointer to the left child
 *  @param rightChild - Pointer to the right child
 */
template <typename dataType>
BinaryTreeNode<dataType>::BinaryTreeNode(dataType data, BinaryTreeNode<dataType>* leftChild,
                                         BinaryTreeNode<dataType>* rightChild)
    : m_data(data), m_leftChild(leftChild), m_rightChild(rightChild) {}

/**
 *  @brief BinaryTreeNode object destructor
 */
template <typename dataType>
BinaryTreeNode<dataType>::~BinaryTreeNode() {}

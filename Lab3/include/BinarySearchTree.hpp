/**
 *  @file      BinarySearchTree.hpp
 *  @brief     Binary Search Tree
 *  @details   ~
 *  @author    JinBridge
 *  @date      2.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once

#include "BinaryTree.hpp"

#include <fstream>

/**
 *  @class   KeyDataPair
 *  @brief   Key Data Pair Class
 *  @details ~
 *  @tparam  keyType  - Type of key
 *  @tparam  dataType - Type of data
 */
template <typename keyType, typename dataType>
class KeyDataPair {
public:
    KeyDataPair(keyType, dataType);
    ~KeyDataPair() = default;

    keyType  getKey() const;
    dataType getData() const;

private:
    keyType  m_key;
    dataType m_data;
};

/**
 *  @brief KeyDataPair object constructor
 *  @param key - Key
 *  @param data - Data
 */
template <typename keyType, typename dataType>
KeyDataPair<keyType, dataType>::KeyDataPair(keyType key, dataType data) : m_key(key), m_data(data) {}

/**
 *  @brief  Get key
 *  @retval keyType - Key
 */
template <typename keyType, typename dataType>
keyType KeyDataPair<keyType, dataType>::getKey() const {
    return m_key;
}

/**
 *  @brief  Get Data
 *  @retval dataType - Data
 */
template <typename keyType, typename dataType>
dataType KeyDataPair<keyType, dataType>::getData() const {
    return m_data;
}

/**
 *  @brief  operator<<
 *  @tparam keyType  - Type of key
 *  @tparam dataType - Type of data
 *  @param  is       - Input stream
 *  @param  it       - Output stream
 *  @retval std::ostream&    - Output stream
 */
template <typename keyType, typename dataType>
std::ostream& operator<<(std::ostream& os, const KeyDataPair<keyType, dataType>& it) {
    os << "(" << it.getKey() << ", " << it.getData() << ")";
    return os;
}

/**
 *  @class   BinarySearchTree
 *  @brief   Binary Search Tree Class
 *  @details ~
 *  @tparam  keyType  - Type of Key
 *  @tparam  dataType - Type of Data
 */
template <typename keyType, typename dataType>
class BinarySearchTree : public BinaryTree<KeyDataPair<keyType, dataType>> {
public:
    BinarySearchTree();
    BinarySearchTree(std::ifstream*);
    ~BinarySearchTree();

    bool search(keyType) const;
    void makeEmpty();

    void insert(keyType, dataType);
    void remove(keyType);

private:
    BinaryTreeNode<KeyDataPair<keyType, dataType>>* removeRecursion(BinaryTreeNode<KeyDataPair<keyType, dataType>>*&,
                                                                    keyType);
    BinaryTreeNode<KeyDataPair<keyType, dataType>>*
    getLeftTreeMax(BinaryTreeNode<KeyDataPair<keyType, dataType>>*) const;
    BinaryTreeNode<KeyDataPair<keyType, dataType>>*
    getRightTreeMin(BinaryTreeNode<KeyDataPair<keyType, dataType>>*) const;

    void updateHeight();
    void updateHeightRecursion(BinaryTreeNode<KeyDataPair<keyType, dataType>>*, int);
};

/**
 *  @brief BinarySearchTree object constructor
 */
template <typename keyType, typename dataType>
BinarySearchTree<keyType, dataType>::BinarySearchTree() : BinaryTree<KeyDataPair<keyType, dataType>>() {}

/**
 *  @brief BinarySearchTree object constructor
 *  @param file - Input file
 */
template <typename keyType, typename dataType>
BinarySearchTree<keyType, dataType>::BinarySearchTree(std::ifstream* file) {
    while (!(*file).eof()) {
        keyType  key;
        dataType data;

        (*file) >> key >> data;
        insert(key, data);
    }
}

/**
 *  @brief BinarySearchTree object destructor
 */
template <typename keyType, typename dataType>
BinarySearchTree<keyType, dataType>::~BinarySearchTree() {}

/**
 *  @brief  Search
 *  @param  key - Key value
 *  @retval bool - True iff key is in the BST
 */
template <typename keyType, typename dataType>
bool BinarySearchTree<keyType, dataType>::search(keyType key) const {
    auto node = BinaryTree<KeyDataPair<keyType, dataType>>::m_root;

    while (node != nullptr) {
        keyType nodeKey = (node->getData()).getKey();
        if (key == nodeKey)
            return true;
        if (key < nodeKey)
            node = node->m_leftChild;
        if (key > nodeKey)
            node = node->m_rightChild;
    }
    return false;
}

/**
 *  @brief Using remove function to remove all nodes
 */
template <typename keyType, typename dataType>
void BinarySearchTree<keyType, dataType>::makeEmpty() {
    while (BinaryTree<KeyDataPair<keyType, dataType>>::m_root) {
        remove((BinaryTree<KeyDataPair<keyType, dataType>>::m_root->m_data).getKey());
    }
}

/**
 *  @brief Insert node
 *  @param keyType - Key
 *  @param dataType - data
 */
template <typename keyType, typename dataType>
void BinarySearchTree<keyType, dataType>::insert(keyType key, dataType data) {
    int dep = 1;

    if (BinaryTree<KeyDataPair<keyType, dataType>>::m_root == nullptr) {
        BinaryTree<KeyDataPair<keyType, dataType>>::m_size++;
        BinaryTree<KeyDataPair<keyType, dataType>>::m_height =
            std::max(BinaryTree<KeyDataPair<keyType, dataType>>::m_height, dep);
        BinaryTree<KeyDataPair<keyType, dataType>>::m_root =
            new BinaryTreeNode<KeyDataPair<keyType, dataType>>(KeyDataPair<keyType, dataType>(key, data));
        return;
    }

    auto node = BinaryTree<KeyDataPair<keyType, dataType>>::m_root;
    while (node != nullptr) {
        keyType nodeKey = (node->getData()).getKey();
        if (key == nodeKey) {
            std::cout << "Key already exists!" << std::endl;
            return;
        }
        if (key < nodeKey) {
            if (node->m_leftChild == nullptr)
                break;
            node = node->m_leftChild;
            dep++;
        }
        if (key > nodeKey) {
            if (node->m_rightChild == nullptr)
                break;
            node = node->m_rightChild;
            dep++;
        }
    }

    if (key < (node->getData()).getKey()) {
        node->m_leftChild =
            new BinaryTreeNode<KeyDataPair<keyType, dataType>>(KeyDataPair<keyType, dataType>(key, data));
    }
    if (key > (node->getData()).getKey()) {
        node->m_rightChild =
            new BinaryTreeNode<KeyDataPair<keyType, dataType>>(KeyDataPair<keyType, dataType>(key, data));
    }

    dep++;
    BinaryTree<KeyDataPair<keyType, dataType>>::m_size++;
    BinaryTree<KeyDataPair<keyType, dataType>>::m_height =
        std::max(BinaryTree<KeyDataPair<keyType, dataType>>::m_height, dep);
}

/**
 *  @brief Remove node
 *  @param keyType - Key
 */
template <typename keyType, typename dataType>
void BinarySearchTree<keyType, dataType>::remove(keyType key) {
    BinaryTree<KeyDataPair<keyType, dataType>>::m_root =
        removeRecursion(BinaryTree<KeyDataPair<keyType, dataType>>::m_root, key);
    updateHeight();
}

/**
 *  @brief  Remove Recursion
 *  @param  root - Root node of subtree
 *  @param  key - Key
 *  @retval BinaryTreeNode<KeyDataPair<keyType, dataType>>* - New root node
 */
template <typename keyType, typename dataType>
BinaryTreeNode<KeyDataPair<keyType, dataType>>*
BinarySearchTree<keyType, dataType>::removeRecursion(BinaryTreeNode<KeyDataPair<keyType, dataType>>*& root,
                                                     keyType                                          key) {
    if (root == nullptr) {
        return nullptr;
    }

    keyType nodeKey = (root->m_data).getKey();
    if (key < nodeKey) {
        root->m_leftChild = removeRecursion(root->m_leftChild, key);
        return root;
    }
    if (key > nodeKey) {
        root->m_rightChild = removeRecursion(root->m_rightChild, key);
        return root;
    }

    if (root->m_leftChild == nullptr && root->m_rightChild == nullptr) {
        delete root;
        root = nullptr;
        BinaryTree<KeyDataPair<keyType, dataType>>::m_size--;
        return nullptr;
    }
    if (root->m_leftChild == nullptr && root->m_rightChild != nullptr) {
        auto tmpPtr = root;
        root        = root->m_rightChild;
        delete tmpPtr;
        BinaryTree<KeyDataPair<keyType, dataType>>::m_size--;
        return root;
    }
    if (root->m_leftChild != nullptr && root->m_rightChild == nullptr) {
        auto tmpPtr = root;
        root        = root->m_leftChild;
        delete tmpPtr;
        BinaryTree<KeyDataPair<keyType, dataType>>::m_size--;
        return root;
    }
    if (root->m_leftChild != nullptr && root->m_rightChild != nullptr) {
        auto replaceNode = getLeftTreeMax(root->m_leftChild);
        if (replaceNode == nullptr) {
            replaceNode = getRightTreeMin(root->m_rightChild);

            root->m_data       = replaceNode->m_data;
            root->m_rightChild = removeRecursion(root->m_rightChild, (replaceNode->m_data).getKey());
            return root;
        }

        root->m_data      = replaceNode->m_data;
        root->m_leftChild = removeRecursion(root->m_leftChild, (replaceNode->m_data).getKey());
        return root;
    }
    return root;
}

/**
 *  @brief  Get max value in left subtree
 *  @param  left - Root node of left subtree
 *  @retval BinaryTreeNode<KeyDataPair<keyType, dataType>>* - New root node of left subtree
 */
template <typename keyType, typename dataType>
BinaryTreeNode<KeyDataPair<keyType, dataType>>*
BinarySearchTree<keyType, dataType>::getLeftTreeMax(BinaryTreeNode<KeyDataPair<keyType, dataType>>* left) const {
    if (left == nullptr) {
        return nullptr;
    }
    if (left->m_rightChild == nullptr) {
        return left;
    }
    return getLeftTreeMax(left->m_rightChild);
}

/**
 *  @brief
 *  @param   -
 *  @retval  -
 */
template <typename keyType, typename dataType>
BinaryTreeNode<KeyDataPair<keyType, dataType>>*
BinarySearchTree<keyType, dataType>::getRightTreeMin(BinaryTreeNode<KeyDataPair<keyType, dataType>>* right) const {
    if (right == nullptr) {
        return nullptr;
    }
    if (right->m_leftChild == nullptr) {
        return right;
    }
    return getLeftTreeMax(right->m_leftChild);
}

/**
 *  @brief Update height after remove
 */
template <typename keyType, typename dataType>
void BinarySearchTree<keyType, dataType>::updateHeight() {
    BinaryTree<KeyDataPair<keyType, dataType>>::m_height = 0;
    updateHeightRecursion(BinaryTree<KeyDataPair<keyType, dataType>>::m_root, 1);
}

/**
 *  @brief Update height recursion
 *  @param node - Root node
 *  @param dep - Current depth
 */
template <typename keyType, typename dataType>
void BinarySearchTree<keyType, dataType>::updateHeightRecursion(BinaryTreeNode<KeyDataPair<keyType, dataType>>* node,
                                                                int                                             dep) {
    if (node == nullptr)
        return;
    BinaryTree<KeyDataPair<keyType, dataType>>::m_height =
        std::max(BinaryTree<KeyDataPair<keyType, dataType>>::m_height, dep);
    updateHeightRecursion(node->m_leftChild, dep + 1);
    updateHeightRecursion(node->m_rightChild, dep + 1);
}

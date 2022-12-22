/**
 *  @file      BinaryTree.hpp
 *  @brief     Binary Tree Node and Binary Tree Class
 *  @details   ~
 *  @author    JinBridge
 *  @date      2.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once

#include <iostream>
#include <queue>
#include <string>

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

    dataType getData() const;

    // private:
    dataType                  m_data;
    BinaryTreeNode<dataType>* m_leftChild;
    BinaryTreeNode<dataType>* m_rightChild;
};

/**
 *  @brief BinaryTreeNode object constructor
 *  @param data - Data of the node
 */
template <typename dataType>
BinaryTreeNode<dataType>::BinaryTreeNode(dataType data) : m_data(data), m_leftChild(nullptr), m_rightChild(nullptr) {}

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

/**
 *  @brief  Get Node Data
 *  @retval dataType - Data
 */
template <typename dataType>
dataType BinaryTreeNode<dataType>::getData() const {
    return m_data;
}

/**
 *  @class   BinaryTree
 *  @brief   Binary Tree Class
 *  @details ~
 *  @tparam  dataType - Type of data
 */
template <typename dataType>
class BinaryTree {
public:
    BinaryTree();
    BinaryTree(dataType*, int);
    BinaryTree(dataType*, dataType*, int);
    ~BinaryTree();

    void inOrder(void (*)(dataType));
    void preOrder(void (*)(dataType));
    void postOrder(void (*)(dataType));
    void levelOrder(void (*)(dataType));

    bool isEmpty() const;
    int  height() const;
    int  size() const;

    void print() const;
    void swapTree();

protected:
    BinaryTreeNode<dataType>* constructRecursion(dataType*, int, int, int);
    BinaryTreeNode<dataType>* constructRecursion(dataType*, dataType*, int, int);
    void                      destructionRecursion(BinaryTreeNode<dataType>*);

    void inOrderRecursion(BinaryTreeNode<dataType>*, void (*)(dataType));
    void preOrderRecursion(BinaryTreeNode<dataType>*, void (*)(dataType));
    void postOrderRecursion(BinaryTreeNode<dataType>*, void (*)(dataType));

    void printRecursion(std::string, BinaryTreeNode<dataType>*, bool) const;
    void swapTreeRecursion(BinaryTreeNode<dataType>*);

    BinaryTreeNode<dataType>* m_root;
    int                       m_size;
    int                       m_height;
};

/**
 *  @brief BinaryTree object constructor
 */
template <typename dataType>
BinaryTree<dataType>::BinaryTree() : m_root(nullptr), m_size(0), m_height(0) {}

/**
 *  @brief BinaryTree object constructor
 *  @param data - Data array with length of len + 1
 *  @param len - Length of data array
 */
template <typename dataType>
BinaryTree<dataType>::BinaryTree(dataType* data, int len) {
    m_size   = len;
    m_height = 1;
    m_root   = constructRecursion(data, len, 1, 1);
}

/**
 *  @brief BinaryTree object constructor
 *  @param preSeq - Pre-order sequence
 *  @param inSeq - In-order Sequence
 *  @param len - Length of sequence
 */
template <typename dataType>
BinaryTree<dataType>::BinaryTree(dataType* preSeq, dataType* inSeq, int len) {
    m_size   = len;
    m_height = 1;
    m_root   = constructRecursion(preSeq, inSeq, len, 1);
}

/**
 *  @brief BinaryTree object destructor
 */
template <typename dataType>
BinaryTree<dataType>::~BinaryTree() {
    destructionRecursion(m_root);
}

/**
 *  @brief In-order recursion
 *  @param func - Operating function
 */
template <typename dataType>
void BinaryTree<dataType>::inOrder(void (*func)(dataType)) {
    inOrderRecursion(m_root, func);
}

/**
 *  @brief Pre-order recursion
 *  @param func - Operating function
 */
template <typename dataType>
void BinaryTree<dataType>::preOrder(void (*func)(dataType)) {
    preOrderRecursion(m_root, func);
}

/**
 *  @brief Post-order recursion
 *  @param func - Operating function
 */
template <typename dataType>
void BinaryTree<dataType>::postOrder(void (*func)(dataType)) {
    postOrderRecursion(m_root, func);
}

/**
 *  @brief Level-order recursion
 *  @param func - Operating function
 */
template <typename dataType>
void BinaryTree<dataType>::levelOrder(void (*func)(dataType)) {
    std::queue<dataType>                  res;
    std::queue<BinaryTreeNode<dataType>*> tmp;
    tmp.push(m_root);
    while (!tmp.empty()) {
        BinaryTreeNode<dataType>* node = tmp.front();
        res.push(node->m_data);
        tmp.pop();

        if (node->m_leftChild) {
            tmp.push(node->m_leftChild);
        }
        if (node->m_rightChild) {
            tmp.push(node->m_rightChild);
        }
    }

    while (!res.empty()) {
        func(res.front());
        res.pop();
    }
}

/**
 *  @brief  Return whether the tree is empty
 *  @retval bool - True iff the tree is empty
 */
template <typename dataType>
inline bool BinaryTree<dataType>::isEmpty() const {
    return (m_size == 0);
}

/**
 *  @brief  Return the height of the tree
 *  @retval int - The height of the tree
 */
template <typename dataType>
int BinaryTree<dataType>::height() const {
    return m_height;
}

/**
 *  @brief  Return the size of the tree
 *  @retval int - Tree size
 */
template <typename dataType>
int BinaryTree<dataType>::size() const {
    return m_size;
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
BinaryTreeNode<dataType>* BinaryTree<dataType>::constructRecursion(dataType* dataArray, int len, int num, int dep) {
    if (num > len || !dataArray[num]) {
        return nullptr;
    }

    m_height = std::max(dep, m_height);

    BinaryTreeNode<dataType>* retPtr = new BinaryTreeNode<dataType>(dataArray[num]);

    retPtr->m_leftChild  = constructRecursion(dataArray, len, num * 2, dep + 1);
    retPtr->m_rightChild = constructRecursion(dataArray, len, num * 2 + 1, dep + 1);

    return retPtr;
}

/**
 *  @brief  Recursion construction function
 *  @param  preSeq - Pre-order Sequence
 *  @param  inSeq - In-order Sequence
 *  @param  len - Length of sequence
 *  @retval BinaryTreeNode<dataType>* - Pointer to the constructing node
 */
template <typename dataType>
BinaryTreeNode<dataType>* BinaryTree<dataType>::constructRecursion(dataType* preSeq, dataType* inSeq, int len,
                                                                   int dep) {

    BinaryTreeNode<dataType>* retPtr = new BinaryTreeNode<dataType>(preSeq[0]);

    if (len == 0) {
        return nullptr;
    }

    m_height = std::max(m_height, dep);

    if (len == 1) {
        return retPtr;
    }

    int pos = 0;
    for (; pos < len; pos++) {
        if (inSeq[pos] == preSeq[0]) {
            break;
        }
    }

    int ltLen = pos;
    int rtLen = len - 1 - pos;

    dataType* ltPreSeq = new dataType[ltLen];
    dataType* ltInSeq  = new dataType[ltLen];
    dataType* rtPreSeq = new dataType[rtLen];
    dataType* rtInSeq  = new dataType[rtLen];

    for (int i = 1; i <= ltLen; ++i) {
        ltPreSeq[i - 1] = preSeq[i];
    }
    for (int i = 0; i < ltLen; ++i) {
        ltInSeq[i] = inSeq[i];
    }

    for (int i = ltLen + 1, j = 0; i < len; ++i) {
        rtPreSeq[j++] = preSeq[i];
    }
    for (int i = ltLen + 1, j = 0; i < len; ++i) {
        rtInSeq[j++] = inSeq[i];
    }

    retPtr->m_leftChild  = constructRecursion(ltPreSeq, ltInSeq, ltLen, dep + 1);
    retPtr->m_rightChild = constructRecursion(rtPreSeq, rtInSeq, rtLen, dep + 1);

    delete[] ltPreSeq;
    delete[] ltInSeq;
    delete[] rtPreSeq;
    delete[] rtInSeq;

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
 *  @brief In-order recursion function
 *  @param func - Operating function
 */
template <typename dataType>
void BinaryTree<dataType>::inOrderRecursion(BinaryTreeNode<dataType>* node, void (*func)(dataType)) {
    if (node == nullptr)
        return;
    if (node->m_leftChild == nullptr && node->m_rightChild == nullptr) {
        func(node->m_data);
        return;
    }

    inOrderRecursion(node->m_leftChild, func);
    func(node->m_data);
    inOrderRecursion(node->m_rightChild, func);
}

/**
 *  @brief Pre-order recursion function
 *  @param func - Operating function
 */
template <typename dataType>
void BinaryTree<dataType>::preOrderRecursion(BinaryTreeNode<dataType>* node, void (*func)(dataType)) {
    if (node == nullptr)
        return;
    if (node->m_leftChild == nullptr && node->m_rightChild == nullptr) {
        func(node->m_data);
        return;
    }

    func(node->m_data);
    preOrderRecursion(node->m_leftChild, func);
    preOrderRecursion(node->m_rightChild, func);
}

/**
 *  @brief Post-order recursion function
 *  @param func - Operating function
 */
template <typename dataType>
void BinaryTree<dataType>::postOrderRecursion(BinaryTreeNode<dataType>* node, void (*func)(dataType)) {
    if (node == nullptr)
        return;
    if (node->m_leftChild == nullptr && node->m_rightChild == nullptr) {
        func(node->m_data);
        return;
    }

    preOrderRecursion(node->m_leftChild, func);
    preOrderRecursion(node->m_rightChild, func);
    func(node->m_data);
}

/**
 *  @brief Recursion print function
 *  @param prefix - Prefix string
 *  @param node - Current node
 *  @param isLeft - Is left child
 */
template <typename dataType>
void BinaryTree<dataType>::printRecursion(std::string prefix, BinaryTreeNode<dataType>* node, bool isLeft) const {
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

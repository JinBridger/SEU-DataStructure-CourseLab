/**
 *  @file      AVLTree.hpp
 *  @brief     AVLTree class
 *  @details   ~
 *  @author    JinBridge
 *  @date      30.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once

#include <iostream>
#include <string>

template <typename DT>
class AVLTree;

template <typename DT>
class AVLTreeNode {
public:
    friend class AVLTree<DT>;

    AVLTreeNode(const DT& data, AVLTreeNode* left = nullptr, AVLTreeNode* right = nullptr)
        : m_data(data), m_height(1), m_leftChild(left), m_rightChild(right) {}
    ~AVLTreeNode() {
        if (m_leftChild)
            delete m_leftChild;
        if (m_rightChild)
            delete m_rightChild;
    }

    DT getData() const {
        return m_data;
    }

private:
    int getBalanceFactor() const {
        int ltHeight = 0, rtHeight = 0;
        if (m_leftChild)
            ltHeight = m_leftChild->m_height;
        if (m_rightChild)
            rtHeight = m_rightChild->m_height;
        return ltHeight - rtHeight;
    }

    void updateHeight() {
        int ltHeight = 0, rtHeight = 0;
        if (m_leftChild)
            ltHeight = m_leftChild->m_height;
        if (m_rightChild)
            rtHeight = m_rightChild->m_height;
        m_height = std::max(ltHeight, rtHeight) + 1;
    }

    DT  m_data;
    int m_height;

    AVLTreeNode* m_leftChild;
    AVLTreeNode* m_rightChild;
};

template <typename DT>
class AVLTree {
public:
    AVLTree() : m_root(nullptr) {}
    ~AVLTree() {
        if (m_root != nullptr)
            delete m_root;
    }

    void insert(const DT& d) {
        insertRecursion(d, m_root);
        m_root = rebalance(m_root);
    }

    void remove(const DT& d) {
        removeRecursion(d, m_root);
        m_root = rebalance(m_root);
    }

    void print() const {
        printRecursion(m_root, "", false);
    }

private:
    AVLTreeNode<DT>* LL_rotation(AVLTreeNode<DT>* x) {
        //          x            y
        //         / \          / \
        // from   y   c   to   a   x
        //       / \              / \
        //      a   b            b   c

        AVLTreeNode<DT>* y = x->m_leftChild;
        AVLTreeNode<DT>* b = y->m_rightChild;

        y->m_rightChild = x;
        x->m_leftChild  = b;

        x->updateHeight();
        y->updateHeight();

        return y;
    }

    AVLTreeNode<DT>* RR_rotation(AVLTreeNode<DT>* y) {
        //         y             x
        //        / \           / \
        // from  a   x   to    y   c
        //          / \       / \
        //         b   c     a   b

        AVLTreeNode<DT>* x = y->m_rightChild;
        AVLTreeNode<DT>* b = x->m_leftChild;

        y->m_rightChild = b;
        x->m_leftChild  = y;

        y->updateHeight();
        x->updateHeight();

        return x;
    }

    AVLTreeNode<DT>* LR_rotation(AVLTreeNode<DT>* z) {
        //            z               z                x
        //           / \             / \              / \
        // from     y   d   to      x   d   to      y      z
        //         / \             / \             / \    / \
        //        a   x           y   c           a   b  c   d
        //           / \         / \    
        //          b   c       a   b

        AVLTreeNode<DT>* y = z->m_leftChild;

        z->m_leftChild = RR_rotation(y);
        return LL_rotation(z);
    }

    AVLTreeNode<DT>* RL_rotation(AVLTreeNode<DT>* z) {
        //            z                 z                  x
        //           / \               / \                / \
        // from     a   y     to      a   x     get     z      y
        //             / \               / \           / \    / \
        //            x   d             b   y         a   b  c   d
        //           / \                   / \
        //          b   c                 c   d

        AVLTreeNode<DT>* y = z->m_rightChild;

        z->m_rightChild = LL_rotation(y);
        return RR_rotation(z);
    }

    /**
     *  @brief  rebalance the node according to the balance factor
     *  @param  node - node
     *  @retval      - new node
     */
    AVLTreeNode<DT>* rebalance(AVLTreeNode<DT>* node) {
        if (node == nullptr)
            return nullptr;

        node->updateHeight();
        int balanceFactor = node->getBalanceFactor();
        if (balanceFactor > 1 && node->m_leftChild->getBalanceFactor() > 0) {  // LL
            print();

            std::cout << "Perform LL Rotation at: " << node->m_data << std::endl;

            return LL_rotation(node);
        }
        if (balanceFactor < -1 && node->m_rightChild->getBalanceFactor() < 0) {  // RR
            print();

            std::cout << "Perform RR Rotation at: " << node->m_data << std::endl;

            return RR_rotation(node);
        }
        if (balanceFactor > 1 && node->m_leftChild->getBalanceFactor() < 0) {  // LR
            print();

            std::cout << "Perform LR Rotation at: " << node->m_data << std::endl;

            return LR_rotation(node);
        }
        if (balanceFactor < -1 && node->m_rightChild->getBalanceFactor() > 0) {  // RL
            print();

            std::cout << "Perform RL Rotation at: " << node->m_data << std::endl;

            return RL_rotation(node);
        }
        return node;
    }

    /**
     *  @brief  remove minimal node of the subtree
     *  @param  node - root of subtree
     *  @retval      - removed value
     */
    DT removeMinNode(AVLTreeNode<DT>*& node) {
        if (node->m_leftChild) {
            DT ret = removeMinNode(node->m_leftChild);
            node->updateHeight();
            return ret;
        }

        DT               ret        = node->m_data;
        AVLTreeNode<DT>* removeNode = node;
        node                        = node->m_rightChild;
        removeNode->m_rightChild    = nullptr;
        delete removeNode;
        return ret;
    }

    void insertRecursion(const DT& d, AVLTreeNode<DT>*& node) {
        if (node == nullptr) {
            node = new AVLTreeNode<DT>(d);
        } else {
            if (node->m_data == d) {
                return;
            }
            if (d < node->m_data) {
                insertRecursion(d, node->m_leftChild);
            } else {
                insertRecursion(d, node->m_rightChild);
            }
        }

        node = rebalance(node);
    }

    void removeRecursion(const DT& d, AVLTreeNode<DT>*& node) {
        if (node == nullptr)
            return;

        if (node->m_data == d) {
            if (node->m_rightChild) {
                node->m_data = removeMinNode(node->m_rightChild);
            } else {
                AVLTreeNode<DT>* removeNode = node;
                node                        = node->m_leftChild;
                removeNode->m_leftChild     = nullptr;
                delete removeNode;
            }
        } else {
            if (d < node->m_data)
                removeRecursion(d, node->m_leftChild);
            else
                removeRecursion(d, node->m_rightChild);
        }

        node = rebalance(node);
    }

    void printRecursion(AVLTreeNode<DT>* node, std::string prefix, bool isLeft) const {
        if (node == nullptr)
            return;

        std::cout << prefix;

        std::cout << (isLeft ? "©À©¤©¤" : "©¸©¤©¤");
        std::cout << node->m_data << std::endl;

        printRecursion(node->m_leftChild, prefix + (isLeft ? "|   " : "    "), true);
        printRecursion(node->m_rightChild, prefix + (isLeft ? "|   " : "    "), false);
    }

    AVLTreeNode<DT>* m_root;
};
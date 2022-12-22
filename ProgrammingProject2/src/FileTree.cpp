/**
 *  @file      FileTree.cpp
 *  @brief     FileTree & FileTreeNode class source code
 *  @details   ~
 *  @author    JinBridge
 *  @date      20.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */

#include "FileTree.h"

#include <iostream>

/**
 *  @brief FileTreeNode object constructor
 *  @param name     - node name
 *  @param isFolder - true: node is a folder
 */
FileTreeNode::FileTreeNode(MyStr name, bool isFolder) : m_name(name), m_isFolder(isFolder) {}

/**
 *  @brief FileTreeNode object destructor
 */
FileTreeNode::~FileTreeNode() {}

/**
 *  @brief  get node's name
 *  @retval  - node's name
 */
MyStr FileTreeNode::getName() const {
    return m_name;
}

/**
 *  @brief FileTree object constructor
 */
FileTree::FileTree() {
    m_root = new FileTreeNode("root", 1);
}

/**
 *  @brief FileTree object destructor
 */
FileTree::~FileTree() {
    destructRecursion(m_root);
    delete m_root;
}

/**
 *  @brief add node to the tree
 *  @param pth - the path of file/folder
 */
void FileTree::add(MyStr pth) {
    MyVec<MyStr> tempVec;

    bool isFolder = (pth[pth.length() - 1] == '\\');
    if (!isFolder) {
        pth = pth + "\\";
    }

    int startPos = 0, curPos = 0;
    while (curPos < pth.length()) {
        if (pth[curPos] == '\\') {
            tempVec.pushBack(pth.substr(startPos, curPos - startPos));
            startPos = curPos + 1;
        }
        curPos++;
    }

    MyVec<MyStr> prefix(tempVec.begin(), tempVec.end() - 1);
    MyStr        name = tempVec[tempVec.size() - 1];

    addNode(prefix, name, isFolder);
}

/**
 *  @brief add node to the tree
 *  @param prefix   - prefix of path
 *  @param name     - name of file/folder
 *  @param isFolder - true: node is a folder
 */
void FileTree::addNode(MyVec<MyStr> prefix, MyStr name, bool isFolder) {
    auto node = m_root;
    addNodeRecursion(node, 0, prefix, name, isFolder);
}

/**
 *  @brief  get output string of name, if is a folder then give it an underline
 *  @param  name     - name
 *  @param  isFolder - true: node is a folder
 *  @retval          - output string
 */
MyStr FileTree::getOutput(MyStr name, bool isFolder) const {
    if (isFolder) {
        return "\033[4m" + name + "\033[0m";
    }
    return name;
}

/**
 *  @brief sort all node by dict order
 */
void FileTree::sortNode() {
    sortNodeRecursion(m_root);
}

/**
 *  @brief  compare function
 *  @param  a -
 *  @param  b -
 *  @retval   - the sequence (dictionary order)
 */
bool cmp(FileTreeNode* a, FileTreeNode* b) {
    if (a->m_isFolder == b->m_isFolder)
        return a->getName() > b->getName();
    return a->m_isFolder < b->m_isFolder;
}

/**
 *  @brief sort all node recursion
 *  @param node - current node
 */
void FileTree::sortNodeRecursion(FileTreeNode* node) {
    node->m_subNode.sort(cmp);

    for (auto t : node->m_subNode) {
        sortNodeRecursion(t);
    }
}

/**
 *  @brief add node recursion
 *  @param node     - current node
 *  @param num      - current pos in prefix
 *  @param prefix   - prefix of the path
 *  @param name     - node name
 *  @param isFolder - true: node is a folder
 */
void FileTree::addNodeRecursion(FileTreeNode* node, int num, MyVec<MyStr> prefix, MyStr name, bool isFolder) {
    if (num == prefix.size()) {
        for (auto subNodePtr : node->m_subNode) {
            if (subNodePtr->m_name == name && subNodePtr->m_isFolder == isFolder) {
                return;
            }
        }
        node->m_subNode.pushBack(new FileTreeNode(name, isFolder));
        return;
    }
    for (auto subNodePtr : node->m_subNode) {
        if (subNodePtr->m_name == prefix[num] && subNodePtr->m_isFolder) {
            addNodeRecursion(subNodePtr, num + 1, prefix, name, isFolder);
            return;
        }
    }
    node->m_subNode.pushBack(new FileTreeNode(prefix[num], 1));
    addNodeRecursion(node->m_subNode[node->m_subNode.size() - 1], num + 1, prefix, name, isFolder);
}

/**
 *  @brief print the tree
 */
void FileTree::print() const {
    printRecursion("", m_root, true);
}

/**
 *  @brief print recursion
 *  @param prefix - the output prefix
 *  @param node   - current node
 *  @param isLast - true: node is the last subnode
 */
void FileTree::printRecursion(MyStr prefix, FileTreeNode* node, bool isLast) const {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (!isLast ? "©À©¤©¤" : "©¸©¤©¤");
        std::cout << getOutput(node->m_name, node->m_isFolder) << std::endl;

        for (auto iter = node->m_subNode.begin(); iter != node->m_subNode.end(); iter++) {
            if (iter == node->m_subNode.end() - 1) {
                printRecursion(prefix + (!isLast ? "©¦   " : "    "), *iter, true);
            }
            else {
                printRecursion(prefix + (!isLast ? "©¦   " : "    "), *iter, false);
            }
        }
    }
}

/**
 *  @brief destruct recursion
 *  @param node - current destructing node
 */
void FileTree::destructRecursion(FileTreeNode* node) {
    if (node->m_subNode.size() == 0) {
        return;
    }
    else {
        for (int i = 0; i < node->m_subNode.size(); ++i) {
            destructRecursion(node->m_subNode[i]);
            delete node->m_subNode[i];
        }
    }
}
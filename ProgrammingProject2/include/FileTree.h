/**
 *  @file      FileTree.h
 *  @brief     FileTree & FileTreeNode class header file
 *  @details   ~
 *  @author    JinBridge
 *  @date      20.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once
#include "MyStr.h"
#include "MyVec.hpp"

class FileTree;

/**
 *  @class   FileTreeNode
 *  @brief   FileTreeNode class
 *  @details ~
 */
class FileTreeNode {
    friend class FileTree;
    friend bool cmp(FileTreeNode*, FileTreeNode*);

public:
    FileTreeNode(MyStr, bool);
    ~FileTreeNode();

    MyStr getName() const;

private:
    MyStr m_name;
    bool  m_isFolder;

    MyVec<FileTreeNode*> m_subNode;
};

/**
 *  @class   FileTree
 *  @brief   FileTree class
 *  @details ~
 */
class FileTree {
public:
    FileTree();
    ~FileTree();

    void add(MyStr);
    void print() const;
    void sortNode();

private:
    MyStr getOutput(MyStr, bool) const;

    void addNode(MyVec<MyStr>, MyStr, bool);

    void sortNodeRecursion(FileTreeNode*);
    void addNodeRecursion(FileTreeNode*, int, MyVec<MyStr>, MyStr, bool);
    void printRecursion(MyStr, FileTreeNode*, bool isLast) const;
    void destructRecursion(FileTreeNode*);

    FileTreeNode* m_root;
};
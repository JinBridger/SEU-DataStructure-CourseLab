#include "FileTree.h"
#include "MyStr.h"
#include "MyVec.hpp"

#include <fstream>
#include <iostream>

int main() {
    std::ifstream is(".\\res\\input.txt");

    int n;
    is >> n;
    MyVec<MyStr> pthVec;
    for (int i = 0; i < n; ++i) {
        MyStr pth;
        is >> pth;
        pthVec.pushBack(pth);
    }

    auto t = FileTree();
    for (auto pth : pthVec) {
        t.add(pth);
    }
    t.sortNode();
    t.print();
}
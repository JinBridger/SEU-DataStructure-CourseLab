#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include "MST.hpp"

int main() {
    std::ifstream nodeFile(".\\res\\node.txt");
    std::ifstream edgeFile(".\\res\\edge.txt");

    int nodeCnt;
    nodeFile >> nodeCnt;
    char* nodeDat = new char[nodeCnt];
    for (int i = 0; i < nodeCnt; ++i)
        nodeFile >> nodeDat[i];

    int edgeCnt;
    edgeFile >> edgeCnt;
    Edge<char, int>* edgeDat = new Edge<char, int>[edgeCnt];
    for (int i = 0; i < edgeCnt; ++i)
        edgeFile >> edgeDat[i].m_from >> edgeDat[i].m_to >> edgeDat[i].m_weight;


    Graph<char, int> test(nodeCnt, nodeDat);
    for (int i = 0; i < edgeCnt; ++i)
        test.addUndirectedEdge(edgeDat[i].m_from, edgeDat[i].m_to, edgeDat[i].m_weight);

    MST(test).printAdjMat();

    delete[] nodeDat;
    delete[] edgeDat;

	return 0;
}
/**
 *  @file      MST.hpp
 *  @brief     prim algorithm
 *  @details   ~
 *  @author    JinBridge
 *  @date      24.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once

#include "Graph.hpp"
#include "MinHeap.hpp"

/**
 *  @brief  prim algorithm
 *  @tparam NodeDataType - type of node data
 *  @tparam EdgeDataType - type of edge data
 *  @param  g            - graph
 *  @retval              - MST
 */
template <typename NodeDataType, typename EdgeDataType>
Graph<NodeDataType, EdgeDataType> MST(const Graph<NodeDataType, EdgeDataType>& g) {
    Graph<NodeDataType, EdgeDataType>         ret(g.m_nodeSize, g.m_node);
    MinHeap<Edge<NodeDataType, EdgeDataType>> hp;

    int* inSet = new int[g.m_nodeSize];
    for (int i = 0; i < g.m_nodeSize; ++i) {
        inSet[i] = 0;
    }

    inSet[0] = 1;
    for (int i = 0; i < g.m_nodeSize; ++i) {
        if (g.m_adjMat[0][i] != 999)
            hp.insert(Edge<NodeDataType, EdgeDataType>(g.m_node[0], g.m_node[i], g.m_adjMat[0][i]));
    }

    for (int i = 1; i < g.m_nodeSize; ++i) {
        std::cout << "MST nodes: ";
        for (int j = 0; j < g.m_nodeSize; ++j) {
            if (inSet[j])
                std::cout << g.m_node[j] << " ";
        }
        std::cout << "\nHeap: " << std::endl;
        hp.print();
        std::cout << std::endl;

        while (inSet[g.getNodeNum(hp.top().m_to)]) {
            hp.pop();
        }
        auto t = hp.pop();
        ret.addUndirectedEdge(t.m_from, t.m_to, t.m_weight);
        inSet[g.getNodeNum(t.m_to)] = 1;
        for (int j = 0; j < g.m_nodeSize; j++) {
            if (!inSet[j] && g.m_adjMat[g.getNodeNum(t.m_to)][j] != 999) {
                hp.insert(Edge<NodeDataType, EdgeDataType>(t.m_to, g.m_node[j], g.m_adjMat[g.getNodeNum(t.m_to)][j]));
            }
        }
    }

    delete[] inSet;

    return ret;
}
/**
 *  @file      Graph.hpp
 *  @brief     Graph template class
 *  @details   ~
 *  @author    JinBridge
 *  @date      23.11.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once
#include <iostream>

/**
 *  @class   Edge
 *  @brief   Edge template class
 *  @details ~
 *  @tparam  NodeDataType - type of node data
 *  @tparam  EdgeDataType - type of edge data
 */
template <typename NodeDataType, typename EdgeDataType>
class Edge {
public:
    Edge(NodeDataType from = 0, NodeDataType to = 0, EdgeDataType weight = 0) : m_from(from), m_to(to), m_weight(weight) {}

    NodeDataType m_from;
    NodeDataType m_to;
    EdgeDataType m_weight;

    friend bool operator<(const Edge& a, const Edge& b) {
        return a.m_weight < b.m_weight;
    }
    friend bool operator<=(const Edge& a, const Edge& b) {
        return a.m_weight < b.m_weight;
    }
    friend bool operator==(const Edge& a, const Edge& b) {
        return a.m_weight == b.m_weight;
    }
    friend bool operator>(const Edge& a, const Edge& b) {
        return a.m_weight > b.m_weight;
    }
    friend bool operator>=(const Edge& a, const Edge& b) {
        return a.m_weight >= b.m_weight;
    }

    friend std::ostream& operator<<(std::ostream& os, const Edge& a) {
        os << "from: " << a.m_from << "\tto: " << a.m_to << "\t weight: " << a.m_weight;
        return os;
    }
};

/**
 *  @class   Graph
 *  @brief   graph template class
 *  @details ~
 *  @tparam  NodeDataType - type of node data
 *  @tparam  EdgeDataType - type of edge data
 */
template <typename NodeDataType, typename EdgeDataType>
class Graph {
public:
    /**
     *  @brief Graph object constructor
     *  @param nodeNum - node number
     */
    Graph(int nodeNum, NodeDataType* arr) : m_nodeSize(nodeNum), m_edgeSize(0) {
        m_node = new NodeDataType[m_nodeSize];
        for (int i = 0; i < m_nodeSize; ++i) {
            m_node[i] = arr[i];
        }
        m_adjMat = new EdgeDataType*[m_nodeSize];
        for (int i = 0; i < m_nodeSize; ++i) {
            m_adjMat[i] = new EdgeDataType[m_nodeSize];
            for (int j = 0; j < m_nodeSize; ++j) {
                m_adjMat[i][j] = (EdgeDataType)999;
            }
        }
    }

    /**
     *  @brief Graph object destructor
     */
    ~Graph() {
        for (int i = 0; i < m_nodeSize; ++i)
            delete[] m_adjMat[i];
        delete[] m_adjMat;
    }

    /**
     *  @brief add directed edge
     *  @param from   - start of edge
     *  @param to     - end of edge
     *  @param weight - length of edge
     */
    void addDirectedEdge(NodeDataType from, NodeDataType to, EdgeDataType weight) {
        int from_pos = getNodeNum(from);
        int to_pos   = getNodeNum(to);
        if (from_pos == -1 || to_pos == -1) {
            throw("Node not exist!");
        }

        m_adjMat[from_pos][to_pos] = weight;
        m_edgeSize++;
    }

    /**
     *  @brief add undirected edge
     *  @param nodeA  - one end of edge
     *  @param nodeB  - other end of edge
     *  @param weight - length of edge
     */
    void addUndirectedEdge(NodeDataType nodeA, NodeDataType nodeB, EdgeDataType weight) {
        addDirectedEdge(nodeA, nodeB, weight);
        addDirectedEdge(nodeB, nodeA, weight);
    }

    /**
     *  @brief print the adjacency matrix of graph
     */
    void printAdjMat() const {
        std::cout << "   \t";
        for (int i = 0; i < m_nodeSize; ++i)
            std::cout << m_node[i] << "\t";
        std::cout << std::endl;
        for (int i = 0; i < m_nodeSize; ++i) {
            std::cout << m_node[i] << ":\t";
            for (int j = 0; j < m_nodeSize; ++j)
                std::cout << m_adjMat[i][j] << "\t";
            std::cout << std::endl;
        }
    }

    int getNodeNum(const NodeDataType& d) const {
        for (int i = 0; i < m_nodeSize; ++i)
            if (m_node[i] == d)
                return i;
        return -1;
    }

    NodeDataType*  m_node;
    EdgeDataType** m_adjMat;

    int m_nodeSize;
    int m_edgeSize;
};

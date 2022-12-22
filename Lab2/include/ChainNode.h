/**
 *  @file      ChainNode.h
 *  @brief     ChainNode Class
 *  @details   ~
 *  @author    JinBridge
 *  @date      11.10.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once

template <typename dataType>
class ChainNode;
template <typename dataType>
class Chain;
template <typename dataType>
void moveLeft(ChainNode<dataType>*&, ChainNode<dataType>*&, int);
template <typename dataType>
void moveRight(ChainNode<dataType>*&, ChainNode<dataType>*&, int);

/**
 *  @class   ChainNode
 *  @brief   The node of chain
 *  @details ~
 *  @tparam  dataType - The type of data
 */
template <typename dataType>
class ChainNode {
    friend class Chain<dataType>;
    friend void moveLeft<dataType>(ChainNode<dataType>*&, ChainNode<dataType>*&, int);
    friend void moveRight<dataType>(ChainNode<dataType>*&, ChainNode<dataType>*&, int);

public:
    ChainNode(const dataType&, ChainNode<dataType>*);

private:
    dataType             m_data;
    ChainNode<dataType>* m_link;
};

/**
 *  @brief ChainNode object constructor
 *  @param data - The data of ChainNode
 *  @param link - The next node pointer of ChainNode
 */
template <typename dataType>
ChainNode<dataType>::ChainNode(const dataType& data, ChainNode<dataType>* link) {
    m_data = data;
    m_link = link;
}
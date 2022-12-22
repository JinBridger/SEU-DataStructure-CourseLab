/**
 *  @file      Ex6.h
 *  @brief     Ex6 solution
 *  @details   ~
 *  @author    JinBridge
 *  @date      13.10.2022
 *  @copyright JinBridge, 2022. All right reserved.
 */
#pragma once
#include "ChainNode.h"

/**
 *  @brief  Move leftPtr to n left
 *  @tparam dataType - type of data
 *  @param  leftPtr  - left pointer
 *  @param  rightPtr - right pointer
 *  @param  n        - move length
 */
template <typename dataType>
void moveLeft(ChainNode<dataType>*& leftPtr, ChainNode<dataType>*& rightPtr, int n) {
    while (leftPtr != nullptr && n > 0) {
        ChainNode<dataType>* tempPtr = leftPtr->m_link;
        leftPtr->m_link              = rightPtr;
        rightPtr                     = leftPtr;
        leftPtr                      = tempPtr;
        n--;
    }
}

/**
 *  @brief  Move rightPtr to n right
 *  @tparam dataType - type of data
 *  @param  leftPtr  - left pointer
 *  @param  rightPtr - right pointer
 *  @param  n        - move length
 */
template <typename dataType>
void moveRight(ChainNode<dataType>*& leftPtr, ChainNode<dataType>*& rightPtr, int n) {
    moveLeft(rightPtr, leftPtr, n);
}
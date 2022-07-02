//
// Created by wjy on 22-7-2.
//

#ifndef DATASTRUCTURE_REDBLACK_H
#define DATASTRUCTURE_REDBLACK_H

#include "../SearchTree/SearchTree.h"

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ( /*RedBlack高度更新条件*/\
(stature((x).lc) == stature((x).rc)) && \
((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)) \
)



template<typename T> //基于BST实现红黑树
class RedBlack : public BST<T>{ //RedBlack模板类
protected:
    void solveDoubleRed(BinNodePosi(T) x);   //双红修正
    void solveDoubleBlack(BinNodePosi(T) x); //双黑修正
    int updateHeight(BinNodePosi(T) x);      //更新节点x的高度
public:
    BinNodePosi(T) insert(const T& e);       //插入
    bool remove(const T& e);                 //删除
//其余接口可直接沿用
};


#endif //DATASTRUCTURE_REDBLACK_H

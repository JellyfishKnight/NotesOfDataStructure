//
// Created by wjy on 22-7-2.
//

#include "RedBlack.h"

template<typename T>                                //更新节点高度
int RedBlack<T>::updateHeight(BinNode<T> *x) {
    x->height = std::max(stature(x->lc), stature(x->rc));  //孩子一般黑高度相等,除非出现双黑
    return IsBlack(x) ? x->height++ : x->height;           //若当前节点为黑,则计入黑深度
}   //因为统一定义stature(NULL) = -1,因此height比黑高度少一,好在不至于影响到算法中的比较判断


template<typename T>                                //将e插入红黑树
BinNode<T> *RedBlack<T>::insert(const T &e) {
    BinNodePosi(T) &x = this->search(e);            //确认目标不存在(留意对_hot的设置)
    if (x) {
        return x;
    }
    x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1); //创建红节点x:以hot为父
    this->_size++;
    solveDoubleRed(x);                              //双红修正过后即可返回
    return x ? x : this->_hot->parent;
} //无论e是否存在在原树中,返回值x->data始终等于e

/**********************************************************
 * RedBlack双红调整算法: 解决节点x与其父亲均为红节点的问题,分为两大类情况
 * RR-1: 2次颜色反转,2次黑高度更新,1~2次旋转,不再递归
 * RR-2: 3次颜色反转,3次黑高度更新,0次旋转,需要递归
 **********************************************************/
template<typename T>
void RedBlack<T>::solveDoubleRed(BinNode<T> *x) {
    if (IsRoot(*x)) {
        this->_root->color = RB_BLACK;
        this->_root->height++;
        return ;
    }
    BinNodePosi(T) p = x->parent;
    if (IsBlack(p)) {
        return ;
    }
    BinNodePosi(T) g = p->parent;
    BinNodePosi(T) u = uncle(x);
    if (IsBlack(u)) {
        if (IsLChild(*x) == IsLChild(*p)) {
            p->color = RB_BLACK;
        } else {
            x->color = RB_BLACK;
        }
        g->color = RB_RED;
        BinNodePosi(T)gg = g->parent;
        BinNodePosi(T)r = FromParentTo(*g) = this->rotateAt(x);
        r->parent = gg;
    } else {
        p->color = RB_BLACK;
        p->height++;
        u->color = RB_BLACK;
        u->height++;
        if (!IsRoot(*g)) {
            g->color = RB_RED;
        }
        solveDoubleRed(g);
    }
}
//
// Created by wjy on 22-6-28.
//

#ifndef DATASTRUCTURE_SPLAYTREE_H
#define DATASTRUCTURE_SPLAYTREE_H

#include "../SearchTree/SearchTree.h"

template<typename T>             //基于BST实现SplayTree
class SplayTree : public BST<T> {  //由BST派生的SplayTree模板类
protected:
    BinNodePosi(T) splay (BinNodePosi(T) v);  //将节点v延伸至树根
public:
    BinNodePosi(T)& search(const T& e);       //查找(重写)
    BinNodePosi(T) insert(const T& e);        //插入(重写)
    bool remove(const T& e);                  //删除(重写)
};

template<typename NodePosi> inline
void attachAsLChild(NodePosi p, NodePosi lc) {
    p->lc = lc;
    if (lc) {
        lc->parent = p;
    }
}

template<typename NodePosi> inline
void attachAsRChild(NodePosi p, NodePosi rc) {
    p->rc = rc;
    if (rc) {
        rc->parent = p;
    }
}

#endif //DATASTRUCTURE_SPLAYTREE_H

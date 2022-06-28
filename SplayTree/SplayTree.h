//
// Created by wjy on 22-6-28.
//

#ifndef DATASTRUCTURE_SPLAYTREE_H
#define DATASTRUCTURE_SPLAYTREE_H

#include "../SearchTree/SearchTree.h"

template<typename T>             //����BSTʵ��SplayTree
class SplayTree : public BST<T> {  //��BST������SplayTreeģ����
protected:
    BinNodePosi(T) splay (BinNodePosi(T) v);  //���ڵ�v����������
public:
    BinNodePosi(T)& search(const T& e);       //����(��д)
    BinNodePosi(T) insert(const T& e);        //����(��д)
    bool remove(const T& e);                  //ɾ��(��д)
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

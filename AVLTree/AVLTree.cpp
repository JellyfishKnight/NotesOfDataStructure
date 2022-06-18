//
// Created by wjy on 22-6-17.
//

#include "AVLTree.h"

template<typename T> //将关键码e插入AVL树中
BinNode<T> *AVLTree<T>::insert(const T &e) {
    BinNodePosi(T)& x = this->search(e);
    if (x) {        //确认目标节点不存在
        return x;
    }
    BinNodePosi(T) xx = x = new BinNode<T>(e,this->_hot);   //创建新节点
//此时,父亲_hot若增高,则其祖父有可能失衡
    this->_size++; //从x之父出发向上,逐层检查各代祖先g
    for (BinNodePosi(T) g = this->_hot; g; g = g->parent) {
        if (!AvlBalanced(*g)) {                             //一旦发现g失衡,则采用"3 + 4"的算法使其复衡,并将子树
            (IsRoot(*g) ? this->_root : (IsLChild(*g) ? g->parent->lc : g->parent->rc)) = this->rotateAt(tallerChild(tallerChild(g)));
            //重新接入原树
            break;
        } else {         //否则(g依然平衡)
            this->updateHeight(g);       //更新其高度即可
        }
    }       //至多只需要一次调整,若果真做过调整,则全树高度必然复原
    return xx;  //返回新节点位置
}           //无论e是否存在于原树中,总有AVL::insert(e)->data == e


template<typename T>  //从AVL树中删除关键码e
bool AVLTree<T>::remove(const T &e) {
    BinNodePosi(T)& x = this->search(e);
    if (!x) {                               //确认目标存在(留意_hot的设置)
        return false;
    }
    removeAt(x, this->_hot);          //先按BST规则删除之(此后,原节点之父_hot以及其祖先均可能失衡)
    this->_size--;
    for (BinNodePosi(T) g = this->_hot; g; g = g->parent) { //从_hot出发向上,逐层检查各代祖先g
        if (!AvlBalanced(*g)) {                             //一旦发现g失衡,采用"3 + 4"方法使其复衡,并将该字数联至
            g = (IsRoot(*g) ? this->_root : (IsLChild(*g) ? g->parent->lc : g->parent->rc)) = this->rotateAt(
                    tallerChild(tallerChild(g)));        //原父亲
        }
        this->updateHeight(g);                           //并更新其高度(即使g没有失衡,其高度也可能降低)
    }                                        //可能需要做O(logn)次调整--无论是否做过调整,全树高度都可能降低
    return true;    //删除成功
}   //若目标节点存在且被删除,返回true,否则返回false





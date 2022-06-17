//
// Created by wjy on 22-6-17.
//

#include "SearchTree.h"

template<typename T> //在以v为根的(AVL,SPLAY,rbTree等)BST子树中查找关键码e
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) {
    if (!v || (e == v->data)) {     //递归基:在节点v(或假想的通配节点)处命中
        return v;
    }
    hot = v;                        //一般情况:先记下当前节点,然后再
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot); //深入一层,递归查找
} //返回时,返回值指向命中节点(或假想的通配哨兵),hot指向其父亲(退化时为初始值NULL)

template<typename T>                //在BST中查找关键字e
BinNode<T> *&BST<T>::search(const T &e) {
    return searchIn(this->_root, e, _hot = NULL); //返回目标节点位置的引用,方便后续的插入删除等操作
}

template<typename T>                //将关键码e插入BST树中
BinNode<T> *BST<T>::insert(const T &e) {
    BinNodePosi(T) x = search(e);
    if (x) {                        //确认目标不存在
        return x;
    }
    x = new BinNode<T>(e, _hot);    //创建新的节点x
    this->_size++;                  //更新规模
    this->updateHeightAbove(x);     //更新x以及其历代祖先的高度
    return x;                       //新插入的节点必为叶子
}           //无论e是否在原树中,返回时总有x->data == e

template<typename T>
bool BST<T>::remove(const T &e) {   //从BST树中删除关键码
    BinNodePosi(T)& x = search(e);  //确认目标存在
    if (!x) {
        return false;
    }
    removeAt(x, _hot);              //实施删除
    this->_size++;                  //更新_hot以及其历代祖先高度
    this->updateHeightAbove(_hot);
    return true;
} //删除成功与否,由返回值指示

template<typename T>
static BinNodePosi(T) removeAt (BinNodePosi(T)& x, BinNodePosi(T)& hot) {
    BinNodePosi(T) w = x;           //实际被摘除的节点,初值同x
    BinNodePosi(T) succ = nullptr;  //实际被删除节点的接替者
    if (!HasLChild(*x)) {           //若*x的左子树为空
        succ = x->rc;               //直接将其替换为其右子树
    } else if (!HasRChild(*x)) {    //若*x的右子树为空
        succ = x->lc;               //直接将其替换为其左子树
    } else {                        //若左右子树均存在,则选择x的直接后继作为实际被摘除的节点
        w = w->succ();              //在左右子树中找到*x的直接后继*w
        std::swap(x->data, w->data);//交换*x和*w的数据元素
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc;  //隔离节点*w
    }
    hot = w->parent;                //记录实际被删除节点的父亲
    if (succ) {                     //并将被删除节点的接替者与hot相连
        succ->parent = hot;
    }
    delete w;                       //释放被摘除节点,返回接替者
    return succ;
}
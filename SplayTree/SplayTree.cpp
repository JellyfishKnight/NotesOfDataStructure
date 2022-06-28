//
// Created by wjy on 22-6-28.
//

#include "SplayTree.h"

template<typename T> //SplayTree伸展算法
BinNode<T> *SplayTree<T>::splay(BinNode<T> *v) { //v因为最近访问而需要伸展节点的位置
    if (!v) {
        return nullptr;
    }
    BinNodePosi(T) p;                            //*v的父亲和祖父
    BinNodePosi(T) g;
    while ((p = v->parent) && (g = p->parent)) { //自下而上,反复对*v做双层伸展
        BinNodePosi(T) gg = g->parent;           //每轮伸展之后*v都以原曾祖父为父
        if (IsLChild(*v)) {
            if (IsLChild(*p)) {                  //zig-zig
                attachAsLChild(g, p->rc);
                attachAsLChild(p, v->rc);
                attachAsRChild(p, g);
                attachAsRChild(v, p);
            } else {                             //zig-zag
                attachAsRChild(p, v->rc);
                attachAsRChild(g, v->lc);
                attachAsLChild(v, g);
                attachAsRChild(v, p);
            }
        } else if (IsRChild(*p)) {               //zag-zag
            attachAsRChild(g, p->lc);
            attachAsRChild(p, v->lc);
            attachAsLChild(p, g);
            attachAsLChild(v, p);
        } else {                                 //zag-zig
            attachAsRChild(p, v->lc);
            attachAsLChild(g, v->rc);
            attachAsRChild(v, g);
            attachAsLChild(v, p);
        }
        if (!gg) {                               //如果*v原先的曾祖父*gg不存在,则*v现在已经是树根
            v->parent = nullptr;
        } else {                                 //否则*gg此后应该以*v作为左孩子或右孩子
            (g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
        }
        this->updateHeight(g);
        this->updateHeight(p);
        this->updateHeight(v);
    }                                            //双层伸展结束时,必有g == nullptr,但是p可能非空
    if (p = v->parent) {                         //如果p真为非空,则额外在做一次单旋
        if (IsLChild(*v)) {
            attachAsLChild(p, v->rc);
            attachAsRChild(v, p);
        } else {
            attachAsRChild(p, v->lc);
            attachAsLChild(v, p);
        }
        this->updateHeight(p);
        this->updateHeight(v);
    }
    v->parent = nullptr;
    return v;
} //调整之后新树根应为被伸展的节点,因此返回该节点位置以便上层函数更新树根

template<typename T> //在伸展树中查找e
BinNode<T> *&SplayTree<T>::search(const T &e) {
    BinNodePosi(T) p = searchIn(this->_root, e, this->_hot = nullptr);
    this->_root = splay(p ? p : this->_hot);    //将最后一个被访问的节点伸展到树根
    return this->_root;
} //与其他BST不同,无论查找成功与否,_root最终都将指向最后被访问的节点


template<typename T>
BinNode<T> *SplayTree<T>::insert(const T &e) { //将关键码e插入伸展树中
    if (!this->_root) {                        //处理原树为空的退化阶段
        this->_size++;
        return this->_root = new BinNode<T>(e);
    }
    if (e == search(e)->data) {                //确认目标节点不存在
        return this->_root;
    }
    this->_size++;                             //创建新节点,一下调整<=7个指针来完成局部重构
    BinNodePosi(T) t = this->_root;
    if (this->_root->data < e) {               //插入新根,以t和t->rc为左右孩子
        t->parent = this->_root = new BinNode<T>(e, nullptr, t, t->rc); //2 + 3个
        if (HasRChild(*t)) {                   // <= 2 个
            t->rc->parent = this->_root;
            t->rc  = nullptr;
        }
    } else {                                   //插入新根,以t->lc和t作为左右孩子
        t->parent = this->_root = new BinNode<T>(e, nullptr, t->lc, t); // 2 + 3个
        if (HasLChild(*t)) {                   //<= 2 个
            t->lc->parent = this->_root;
            t->lc = nullptr;
        }
    }
    this->updateHeightAbove(t);             //更新t以及其祖先(实际上只有_root一个)的高度
    return this->_root;                        //新节点必然置于树根,返回之
}                                              //无论e是否存在与原树中,返回时总有_root->data = e


template<typename T>                           //从伸展树中删除关键码e
bool SplayTree<T>::remove(const T &e) {
    if (!this->_root || (e != search(e)->data)) { //若树空或者目标不存在,则无法删除
        return false;
    }
    BinNodePosi(T) w = this->_root;            //经过search过后e已经到了树根
    if (!HasLChild(*this->_root)) {            //如果没有左子树,就直接删除
        this->_root = this->_root->rc;
        if (this->_root) {
            this->_root->parent = nullptr;
        }
    } else if (!HasRChild(*this->_root)) {     //如果没有右子树也直接删除
        this->_root = this->_root->lc;
        if (this->_root) {
            this->_root->parent = nullptr;
        }
    } else {                                   //如果左右子树同时存在,那么
        BinNodePosi(T) lTree = this->_root->lc;//暂时将左子树切除
        lTree->parent = nullptr;
        this->_root->lc = nullptr;
        this->_root = this->_root->rc;         //只保留右子树
        this->_root->parent = nullptr;
        search(w->data);                    //以原树根为目标,做一次(必定失败的)查找
        this->_root->lc = lTree;               //只需要将原左子树接回原位即可
        lTree->parent = this->_root;
    }
    delete w;                                  //释放节点,更新规模
    this->_size--;
    if (this->_root) {
        this->updateHeight(this->_root);
    }
    return true;
} //如果目标节点存在并且被删除,返回true,否则返回false


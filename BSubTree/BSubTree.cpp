//
// Created by wjy on 22-6-28.
//

#include "BSubTree.h"

template<typename T>  //在B-树中查找关键码e
BTNode<T> *BTree<T>::search(const T &e) {
    BTNodePosi(T) v = _root; //从根节点出发
    _hot = nullptr;
    while (v) {              //逐层查找
        Rank r = v->key.search(e); //在当前节点中,找到不大于e的最大关键码
        if ((0 <= r) && (e == v->key[r])) { //成功:当前节点命中关键码
            return v;
        }
        _hot = v;            //否则转入对应子树(_hot指向其父亲)----需要做I/O,最花费时间
        v = v->child[r + 1];
    } //这里在向量内是二分查找,但是对通常的_order可直接顺序查找
    return nullptr; //失败:最终抵达外部节点
}

template<typename T> //将关键码e插入到B-树中
bool BTree<T>::insert(const T &e) {
    BTNodePosi(T) v = search(e); //确认目标节点不存在
    if (v) {
        return false;
    }
    Rank r = _hot->key.search(e);//在节点_hot的有序关键码向量中查找合适的插入位置
    _hot->key.insert(r + 1, e);  //将新的关键码插入到对应的位置
    _hot->child.insert(r + 2, nullptr); //创建一个空子树指针
    _size++;                     //更新全树规模
    solveOverflow(_hot);         //如果有必要,需要做分裂
    return true;                 //插入成功
}

template<typename T>             //关键码插入后若节点上溢,则做节点分裂处理
void BTree<T>::solveOverflow(BTNode<T> *v) {
    if (_order >= v->child.size()) { //递归基:当前节点并未上溢
        return ;
    }
    Rank s = _order / 2;         //轴点(此时应该有_order = key.size() = child.size() - 1)
    BTNodePosi(T) u = new BTNode<T>(); //注意:新节点已经有一个孩子
    for (Rank j = 0; j < _order - s - 1; j++) { //v右侧order-s-1个孩子以及关键码分裂为右节点
        u->child.insert(j, v->child->remove(s + 1)); //逐个移动效率低
        u->key.insert(j, v->key.remove(s + 1));      //此策略可改进
    }
    u->child[_order - s - 1] = v->child.remove(s + 1); //移动v最靠右的孩子
    if (u->child[0]) {           //如果u的孩子非空
        for (Rank j = 0; j < _order - s; j++) { //令它们的父节点统一
            u->child[j]->parent = u;
        }
    }
    BTNodePosi(T) p = v->parent; //v当前的父节点p
    if (!p) {                    //如果p为空,则创建
        _root = p = new BTNode<T>();
        p->child[0] = v->parent = p;
    }
    Rank r = 1 + p->key.search(v->key[0]); //p中指向u的指针的秩
    p->key.insert(r, v->key.remove(s)); //轴点关键码上升
    p->child.insert(r + 1, u);   //新节点u与父节点p互联
    u->parent = p;
    solveOverflow(p);         //上升一层,如果有必要则继续分裂--最多递归O(logn)次
}

template<typename T>
bool BTree<T>::remove(const T &e) {      //从B-树中删除关键码e
    BTNodePosi(T) v = search(e);         //确认目标关键码存在
    if (!v) {
        return false;
    }
    Rank r = v->key.search(e);           //如果v不是叶子,那e的后及必然属于某个叶节点
    if (v->child[0]) {                   //在右子树中一直往左
        BTNodePosi(T) u = v->child[r + 1];
        while (u->child[0]) {            //就可以找出e的后继
            u = u->child[0];
        }
        v->key[r] = u->key[0];           //并与之交换位置
        v = u;
        r = 0;
    }                                    //至此,v必然位于最底层,v并且其中第r个关键码就是待删除者
    v->key.remove(r);                    //删除e,以及其下两个外部节点之一
    v->child.remove(r + 1);
    _size++;
    solveUnderflow(r);                   //如果有必要,就做旋转或者合并
    return true;
}

template<typename T>
void BTree<T>::solveUnderflow(BTNode<T> *v) {
    if ((_order + 1) / 2 <= v->child.size()) {
        return ;
    }
    BTNodePosi(T) p = v->parent;
    if (!p) {
        if (!v->key.size() && v->child[0]) {
            _root = v->child[0];
            _root->parent = nullptr;
            v->child[0] = nullptr;
            delete v;
        }
        return ;
    }
    Rank r = 0;
    while (p->child[r] != v) {
        r++;
    }
    if (r > 0) {
        BTNodePosi(T) ls = p->child[r - 1];
        if ((_order + 1) / 2 < ls->child.size()) {
            v->key.insert(0, p->key[r - 1]);
            p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
            v->child.insert(0, ls->child.remove(ls->child.size() - 1));
            if (v->child[0]) {
                v->child[0]->parent = v;
            }
            return ;
        }
    }
    if (r < p->child.size() - 1) {
        BTNodePosi(T) rs = p->child[r + 1];
        if ((_order + 1) / 2 < rs->child.size()) {
            v->key.insert(v->key.size(), p->key[r]);
            p->key[r] = rs->key.remove(0);
            v->child.insert(v->child.size(), rs->child.remove(0));
            if (v->child[v->child.size() - 1]) {
                v->child[v->child.size() - 1]->parent = v;
            }
            return ;
        }
    }
    if (r > 0) {
        BTNodePosi(T) ls = p->child[r - 1];
        ls->key.insert(ls->key.size(), p->key.remove(r - 1));
        p->child.remove(r);
        ls->child.insert(ls->child.size(), v->child.remove(0));
        if (ls->child[ls->child.size() - 1]) {
            ls->child[ls->child.size() - 1]->parenr = ls;
        }
        while (!v->key.empty()) {
            ls->key.insert(ls->key.size(), v->key.remove(0));
            ls->child.insert(ls->child.size(), v->child.remove(0));
            if (ls->child[ls->child.size() - 1]) {
                ls->child[ls->child.size() - 1]->parent = ls;
            }
        }
        delete v;
    } else {
        BTNodePosi(T) rs = p->child[r + 1];
        rs->key.insert(0, p->key.remove(r));
        p->child.remove(r);
        rs->child.insert(0, v->child.remove(v->child.size() - 1));
        if (rs->child[0]) {
            rs->child[0]->parent = rs;
        }
        while (!v->key.empty()) {
            rs->key.insert(0, v->key.remove(v->key.size() - 1));
            rs->child.insert(0, v->child.remove(v->child.size() - 1));
            if (rs->child[0]) {
                rs->child[0]->parent = rs;
            }
        }
        delete v;
    }
    solveOverflow(p);
    return ;
}
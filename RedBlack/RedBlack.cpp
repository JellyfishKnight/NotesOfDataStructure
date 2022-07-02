//
// Created by wjy on 22-7-2.
//

#include "RedBlack.h"

template<typename T>                                //���½ڵ�߶�
int RedBlack<T>::updateHeight(BinNode<T> *x) {
    x->height = std::max(stature(x->lc), stature(x->rc));  //����һ��ڸ߶����,���ǳ���˫��
    return IsBlack(x) ? x->height++ : x->height;           //����ǰ�ڵ�Ϊ��,���������
}   //��Ϊͳһ����stature(NULL) = -1,���height�Ⱥڸ߶���һ,���ڲ�����Ӱ�쵽�㷨�еıȽ��ж�


template<typename T>                                //��e��������
BinNode<T> *RedBlack<T>::insert(const T &e) {
    BinNodePosi(T) &x = this->search(e);            //ȷ��Ŀ�겻����(�����_hot������)
    if (x) {
        return x;
    }
    x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1); //������ڵ�x:��hotΪ��
    this->_size++;
    solveDoubleRed(x);                              //˫���������󼴿ɷ���
    return x ? x : this->_hot->parent;
} //����e�Ƿ������ԭ����,����ֵx->dataʼ�յ���e

/**********************************************************
 * RedBlack˫������㷨: ����ڵ�x���丸�׾�Ϊ��ڵ������,��Ϊ���������
 * RR-1: 2����ɫ��ת,2�κڸ߶ȸ���,1~2����ת,���ٵݹ�
 * RR-2: 3����ɫ��ת,3�κڸ߶ȸ���,0����ת,��Ҫ�ݹ�
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
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

template<typename T>
bool RedBlack<T>::remove(const T &e) {
    BinNodePosi(T) &x = this->search(e);
    if (!x) {
        return false;
    }
    BinNodePosi(T) r = removeAt(x, this->_hot);
    if (!(--this->_size)) {
        return true;
    }
    if (!this->_hot) {
        this->_root->color = RB_BLACK;
        updateHeight(this->_root);
        return true;
    }
    if (BlackHeightUpdated(*this->_hot)) {
        return true;
    }
    if (IsRed(r)) {
        r->color = RB_BLACK;
        r->height++;
        return true;
    }
    solveDoubleBlack(r);
    return true;
}

template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNode<T> *r) {
    BinNodePosi(T) p = r ? r->parent : this->_hot;
    if (!p) {
        return ;
    }
    BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;
    if (IsBlack(s)) {
        BinNodePosi(T) t = nullptr;
        if (IsRed(s->rc)) {
            t = s->rc;
        }
        if (IsRed(s->lc)) {
            t = s->lc;
        }
        if (t) {
            RBCOLOR oldColor = p->color;
            BinNodePosi(T) b = FromParentTo(*p) = this->rotateAt(t);
            if (HasLChild(*b)) {
                b->lc->color = RB_BLACK;
                updateHeight(b->lc);
            }
            if (HasRChild(*b)) {
                b->rc->color = RB_BLACK;
                updateHeight(b->rc);
            }
            b->color = oldColor;
            updateHeight(b);
        } else {
            s->color = RB_RED;
            s->height--;
            if (IsRed(p)) {
                p->color = RB_BLACK;
            } else {
                p->height--;
                solveDoubleBlack(p);
            }
        }
    } else {
        s->color = RB_BLACK;
        p->color = RB_RED;
        BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;
        this->_hot = p;
        FromParentTo(*p) = this->rotateAt(t);
        solveDoubleBlack(r);
    }
}
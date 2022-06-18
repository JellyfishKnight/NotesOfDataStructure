//
// Created by wjy on 22-6-17.
//

#include "SearchTree.h"

template<typename T> //����vΪ����(AVL,SPLAY,rbTree��)BST�����в��ҹؼ���e
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) {
    if (!v || (e == v->data)) {     //�ݹ��:�ڽڵ�v(������ͨ��ڵ�)������
        return v;
    }
    hot = v;                        //һ�����:�ȼ��µ�ǰ�ڵ�,Ȼ����
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot); //����һ��,�ݹ����
} //����ʱ,����ֵָ�����нڵ�(������ͨ���ڱ�),hotָ���丸��(�˻�ʱΪ��ʼֵNULL)

template<typename T>                //��BST�в��ҹؼ���e
BinNode<T> *&BST<T>::search(const T &e) {
    return searchIn(this->_root, e, _hot = NULL); //����Ŀ��ڵ�λ�õ�����,��������Ĳ���ɾ���Ȳ���
}

template<typename T>                //���ؼ���e����BST����
BinNode<T> *BST<T>::insert(const T &e) {
    BinNodePosi(T) x = search(e);
    if (x) {                        //ȷ��Ŀ�겻����
        return x;
    }
    x = new BinNode<T>(e, _hot);    //�����µĽڵ�x
    this->_size++;                  //���¹�ģ
    this->updateHeightAbove(x);     //����x�Լ����������ȵĸ߶�
    return x;                       //�²���Ľڵ��ΪҶ��
}           //����e�Ƿ���ԭ����,����ʱ����x->data == e

template<typename T>
bool BST<T>::remove(const T &e) {   //��BST����ɾ���ؼ���
    BinNodePosi(T)& x = search(e);  //ȷ��Ŀ�����
    if (!x) {
        return false;
    }
    removeAt(x, _hot);              //ʵʩɾ��
    this->_size++;                  //����_hot�Լ����������ȸ߶�
    this->updateHeightAbove(_hot);
    return true;
} //ɾ���ɹ����,�ɷ���ֵָʾ

template<typename T>
static BinNodePosi(T) removeAt (BinNodePosi(T)& x, BinNodePosi(T)& hot) {
    BinNodePosi(T) w = x;           //ʵ�ʱ�ժ���Ľڵ�,��ֵͬx
    BinNodePosi(T) succ = nullptr;  //ʵ�ʱ�ɾ���ڵ�Ľ�����
    if (!HasLChild(*x)) {           //��*x��������Ϊ��
        succ = x->rc;               //ֱ�ӽ����滻Ϊ��������
    } else if (!HasRChild(*x)) {    //��*x��������Ϊ��
        succ = x->lc;               //ֱ�ӽ����滻Ϊ��������
    } else {                        //����������������,��ѡ��x��ֱ�Ӻ����Ϊʵ�ʱ�ժ���Ľڵ�
        w = w->succ();              //�������������ҵ�*x��ֱ�Ӻ��*w
        std::swap(x->data, w->data);//����*x��*w������Ԫ��
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc;  //����ڵ�*w
    }
    hot = w->parent;                //��¼ʵ�ʱ�ɾ���ڵ�ĸ���
    if (succ) {                     //������ɾ���ڵ�Ľ�������hot����
        succ->parent = hot;
    }
    delete w;                       //�ͷű�ժ���ڵ�,���ؽ�����
    return succ;
}

/*
 * ����"3 + 4"�ṹ���������ڵ��Լ��Ŀ�����,��������֮��ľֲ��������ڵ�λ��(��b)
 * �������ڵ����ϲ�ڵ�֮���˫������,����Ҫ�ϲ���������
 * ������AVL��RedBlack�ľֲ�ƽ�����
 */
template<typename T>
BinNode<T> *
BST<T>::connect34(BinNode<T> * a, BinNode<T> * b, BinNode<T> * c, BinNode<T> * T0, BinNode<T> * T1, BinNode<T> * T2, BinNode<T> * T3) {
    a->lc = T0;
    if (T0) {
        T0->parent = a;
    }
    a->rc = T1;
    if (T1) {
        T1->parent = a;
    }
    c->lc = T2;
    if (T2) {
        T2->parent = c;
    }
    c->rc = T3;
    if (T3) {
        T3->parent = c;
    }
    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    this->updateHeight(b);
    return b;   //�������µĸ��ڵ�
}

/*
 * BST�ڵ���ת�任ͳһ�㷨(3�ڵ� + 4����),���ص���֮��ֲ��������ڵ��λ��
 * ע��: ��������������ȷָ���ϲ�ڵ�(�������),����������ӻ���Ҫ�ϲ㺯�����
 */
template<typename T>
BinNode<T> *BST<T>::rotateAt(BinNode<T> *v) { //vΪ�ǿ����ӱ��ڵ�
    BinNodePosi(T) p = v->parent;             //����v,p,g���λ�÷��������
    BinNodePosi(T) g = p->parent;
    if (IsLChild(*p)) {          //zig
        if (IsLChild(*v)) {         //zig-zig
            p->parent = g->parent;
            return connect34(p, v, g, v->lc, v->rc, p->rc, g->rc);
        } else {                    //zig-zag
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {                     //zag
        if (IsLChild(*v)) {         //zag-zag
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        } else {                    //zag-zig
            v->parent = g->parent;
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
}
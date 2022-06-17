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
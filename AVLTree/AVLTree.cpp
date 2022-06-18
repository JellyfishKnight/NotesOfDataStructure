//
// Created by wjy on 22-6-17.
//

#include "AVLTree.h"

template<typename T> //���ؼ���e����AVL����
BinNode<T> *AVLTree<T>::insert(const T &e) {
    BinNodePosi(T)& x = this->search(e);
    if (x) {        //ȷ��Ŀ��ڵ㲻����
        return x;
    }
    BinNodePosi(T) xx = x = new BinNode<T>(e,this->_hot);   //�����½ڵ�
//��ʱ,����_hot������,�����游�п���ʧ��
    this->_size++; //��x֮����������,������������g
    for (BinNodePosi(T) g = this->_hot; g; g = g->parent) {
        if (!AvlBalanced(*g)) {                             //һ������gʧ��,�����"3 + 4"���㷨ʹ�临��,��������
            (IsRoot(*g) ? this->_root : (IsLChild(*g) ? g->parent->lc : g->parent->rc)) = this->rotateAt(tallerChild(tallerChild(g)));
            //���½���ԭ��
            break;
        } else {         //����(g��Ȼƽ��)
            this->updateHeight(g);       //������߶ȼ���
        }
    }       //����ֻ��Ҫһ�ε���,��������������,��ȫ���߶ȱ�Ȼ��ԭ
    return xx;  //�����½ڵ�λ��
}           //����e�Ƿ������ԭ����,����AVL::insert(e)->data == e


template<typename T>  //��AVL����ɾ���ؼ���e
bool AVLTree<T>::remove(const T &e) {
    BinNodePosi(T)& x = this->search(e);
    if (!x) {                               //ȷ��Ŀ�����(����_hot������)
        return false;
    }
    removeAt(x, this->_hot);          //�Ȱ�BST����ɾ��֮(�˺�,ԭ�ڵ�֮��_hot�Լ������Ⱦ�����ʧ��)
    this->_size--;
    for (BinNodePosi(T) g = this->_hot; g; g = g->parent) { //��_hot��������,������������g
        if (!AvlBalanced(*g)) {                             //һ������gʧ��,����"3 + 4"����ʹ�临��,��������������
            g = (IsRoot(*g) ? this->_root : (IsLChild(*g) ? g->parent->lc : g->parent->rc)) = this->rotateAt(
                    tallerChild(tallerChild(g)));        //ԭ����
        }
        this->updateHeight(g);                           //��������߶�(��ʹgû��ʧ��,��߶�Ҳ���ܽ���)
    }                                        //������Ҫ��O(logn)�ε���--�����Ƿ���������,ȫ���߶ȶ����ܽ���
    return true;    //ɾ���ɹ�
}   //��Ŀ��ڵ�����ұ�ɾ��,����true,���򷵻�false





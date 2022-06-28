//
// Created by wjy on 22-6-28.
//

#include "SplayTree.h"

template<typename T> //SplayTree��չ�㷨
BinNode<T> *SplayTree<T>::splay(BinNode<T> *v) { //v��Ϊ������ʶ���Ҫ��չ�ڵ��λ��
    if (!v) {
        return nullptr;
    }
    BinNodePosi(T) p;                            //*v�ĸ��׺��游
    BinNodePosi(T) g;
    while ((p = v->parent) && (g = p->parent)) { //���¶���,������*v��˫����չ
        BinNodePosi(T) gg = g->parent;           //ÿ����չ֮��*v����ԭ���游Ϊ��
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
        if (!gg) {                               //���*vԭ�ȵ����游*gg������,��*v�����Ѿ�������
            v->parent = nullptr;
        } else {                                 //����*gg�˺�Ӧ����*v��Ϊ���ӻ��Һ���
            (g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
        }
        this->updateHeight(g);
        this->updateHeight(p);
        this->updateHeight(v);
    }                                            //˫����չ����ʱ,����g == nullptr,����p���ܷǿ�
    if (p = v->parent) {                         //���p��Ϊ�ǿ�,���������һ�ε���
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
} //����֮��������ӦΪ����չ�Ľڵ�,��˷��ظýڵ�λ���Ա��ϲ㺯����������

template<typename T> //����չ���в���e
BinNode<T> *&SplayTree<T>::search(const T &e) {
    BinNodePosi(T) p = searchIn(this->_root, e, this->_hot = nullptr);
    this->_root = splay(p ? p : this->_hot);    //�����һ�������ʵĽڵ���չ������
    return this->_root;
} //������BST��ͬ,���۲��ҳɹ����,_root���ն���ָ����󱻷��ʵĽڵ�


template<typename T>
BinNode<T> *SplayTree<T>::insert(const T &e) { //���ؼ���e������չ����
    if (!this->_root) {                        //����ԭ��Ϊ�յ��˻��׶�
        this->_size++;
        return this->_root = new BinNode<T>(e);
    }
    if (e == search(e)->data) {                //ȷ��Ŀ��ڵ㲻����
        return this->_root;
    }
    this->_size++;                             //�����½ڵ�,һ�µ���<=7��ָ������ɾֲ��ع�
    BinNodePosi(T) t = this->_root;
    if (this->_root->data < e) {               //�����¸�,��t��t->rcΪ���Һ���
        t->parent = this->_root = new BinNode<T>(e, nullptr, t, t->rc); //2 + 3��
        if (HasRChild(*t)) {                   // <= 2 ��
            t->rc->parent = this->_root;
            t->rc  = nullptr;
        }
    } else {                                   //�����¸�,��t->lc��t��Ϊ���Һ���
        t->parent = this->_root = new BinNode<T>(e, nullptr, t->lc, t); // 2 + 3��
        if (HasLChild(*t)) {                   //<= 2 ��
            t->lc->parent = this->_root;
            t->lc = nullptr;
        }
    }
    this->updateHeightAbove(t);             //����t�Լ�������(ʵ����ֻ��_rootһ��)�ĸ߶�
    return this->_root;                        //�½ڵ��Ȼ��������,����֮
}                                              //����e�Ƿ������ԭ����,����ʱ����_root->data = e


template<typename T>                           //����չ����ɾ���ؼ���e
bool SplayTree<T>::remove(const T &e) {
    if (!this->_root || (e != search(e)->data)) { //�����ջ���Ŀ�겻����,���޷�ɾ��
        return false;
    }
    BinNodePosi(T) w = this->_root;            //����search����e�Ѿ���������
    if (!HasLChild(*this->_root)) {            //���û��������,��ֱ��ɾ��
        this->_root = this->_root->rc;
        if (this->_root) {
            this->_root->parent = nullptr;
        }
    } else if (!HasRChild(*this->_root)) {     //���û��������Ҳֱ��ɾ��
        this->_root = this->_root->lc;
        if (this->_root) {
            this->_root->parent = nullptr;
        }
    } else {                                   //�����������ͬʱ����,��ô
        BinNodePosi(T) lTree = this->_root->lc;//��ʱ���������г�
        lTree->parent = nullptr;
        this->_root->lc = nullptr;
        this->_root = this->_root->rc;         //ֻ����������
        this->_root->parent = nullptr;
        search(w->data);                    //��ԭ����ΪĿ��,��һ��(�ض�ʧ�ܵ�)����
        this->_root->lc = lTree;               //ֻ��Ҫ��ԭ�������ӻ�ԭλ����
        lTree->parent = this->_root;
    }
    delete w;                                  //�ͷŽڵ�,���¹�ģ
    this->_size--;
    if (this->_root) {
        this->updateHeight(this->_root);
    }
    return true;
} //���Ŀ��ڵ���ڲ��ұ�ɾ��,����true,���򷵻�false


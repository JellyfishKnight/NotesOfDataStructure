//
// Created by wjy on 22-6-28.
//

#include "BSubTree.h"

template<typename T>  //��B-���в��ҹؼ���e
BTNode<T> *BTree<T>::search(const T &e) {
    BTNodePosi(T) v = _root; //�Ӹ��ڵ����
    _hot = nullptr;
    while (v) {              //������
        Rank r = v->key.search(e); //�ڵ�ǰ�ڵ���,�ҵ�������e�����ؼ���
        if ((0 <= r) && (e == v->key[r])) { //�ɹ�:��ǰ�ڵ����йؼ���
            return v;
        }
        _hot = v;            //����ת���Ӧ����(_hotָ���丸��)----��Ҫ��I/O,���ʱ��
        v = v->child[r + 1];
    } //�������������Ƕ��ֲ���,���Ƕ�ͨ����_order��ֱ��˳�����
    return nullptr; //ʧ��:���յִ��ⲿ�ڵ�
}

template<typename T> //���ؼ���e���뵽B-����
bool BTree<T>::insert(const T &e) {
    BTNodePosi(T) v = search(e); //ȷ��Ŀ��ڵ㲻����
    if (v) {
        return false;
    }
    Rank r = _hot->key.search(e);//�ڽڵ�_hot������ؼ��������в��Һ��ʵĲ���λ��
    _hot->key.insert(r + 1, e);  //���µĹؼ�����뵽��Ӧ��λ��
    _hot->child.insert(r + 2, nullptr); //����һ��������ָ��
    _size++;                     //����ȫ����ģ
    solveOverflow(_hot);         //����б�Ҫ,��Ҫ������
    return true;                 //����ɹ�
}

template<typename T>             //�ؼ����������ڵ�����,�����ڵ���Ѵ���
void BTree<T>::solveOverflow(BTNode<T> *v) {
    if (_order >= v->child.size()) { //�ݹ��:��ǰ�ڵ㲢δ����
        return ;
    }
    Rank s = _order / 2;         //���(��ʱӦ����_order = key.size() = child.size() - 1)
    BTNodePosi(T) u = new BTNode<T>(); //ע��:�½ڵ��Ѿ���һ������
    for (Rank j = 0; j < _order - s - 1; j++) { //v�Ҳ�order-s-1�������Լ��ؼ������Ϊ�ҽڵ�
        u->child.insert(j, v->child->remove(s + 1)); //����ƶ�Ч�ʵ�
        u->key.insert(j, v->key.remove(s + 1));      //�˲��ԿɸĽ�
    }
    u->child[_order - s - 1] = v->child.remove(s + 1); //�ƶ�v��ҵĺ���
    if (u->child[0]) {           //���u�ĺ��ӷǿ�
        for (Rank j = 0; j < _order - s; j++) { //�����ǵĸ��ڵ�ͳһ
            u->child[j]->parent = u;
        }
    }
    BTNodePosi(T) p = v->parent; //v��ǰ�ĸ��ڵ�p
    if (!p) {                    //���pΪ��,�򴴽�
        _root = p = new BTNode<T>();
        p->child[0] = v->parent = p;
    }
    Rank r = 1 + p->key.search(v->key[0]); //p��ָ��u��ָ�����
    p->key.insert(r, v->key.remove(s)); //���ؼ�������
    p->child.insert(r + 1, u);   //�½ڵ�u�븸�ڵ�p����
    u->parent = p;
    solveOverflow(p);         //����һ��,����б�Ҫ���������--���ݹ�O(logn)��
}

template<typename T>
bool BTree<T>::remove(const T &e) {      //��B-����ɾ���ؼ���e
    BTNodePosi(T) v = search(e);         //ȷ��Ŀ��ؼ������
    if (!v) {
        return false;
    }
    Rank r = v->key.search(e);           //���v����Ҷ��,��e�ĺ󼰱�Ȼ����ĳ��Ҷ�ڵ�
    if (v->child[0]) {                   //����������һֱ����
        BTNodePosi(T) u = v->child[r + 1];
        while (u->child[0]) {            //�Ϳ����ҳ�e�ĺ��
            u = u->child[0];
        }
        v->key[r] = u->key[0];           //����֮����λ��
        v = u;
        r = 0;
    }                                    //����,v��Ȼλ����ײ�,v�������е�r���ؼ�����Ǵ�ɾ����
    v->key.remove(r);                    //ɾ��e,�Լ����������ⲿ�ڵ�֮һ
    v->child.remove(r + 1);
    _size++;
    solveUnderflow(r);                   //����б�Ҫ,������ת���ߺϲ�
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
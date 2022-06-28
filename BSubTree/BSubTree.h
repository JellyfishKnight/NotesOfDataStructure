//
// Created by wjy on 22-6-28.
//

#ifndef DATASTRUCTURE_BSUBTREE_H
#define DATASTRUCTURE_BSUBTREE_H

#include "../Vector/Vector.h"

#define BTNodePosi(T) BTNode<T>*         //B-���ڵ�λ��

template<typename T>                     //B-���ڵ�ģ����
struct BTNode {
//��Ա(Ϊ������ͳһ����)
    BTNodePosi(T) parent;                //���ڵ�
    Vector<T> key;                       //�ؼ������
    Vector<BTNodePosi(T)> child;         //���ӱ���(�䳤���ܱ�key��һ)
//���캯��(ע��:BTNodeֻ����Ϊ���ڵ㴴��,���ҳ�ʼʱ��0���ؼ����1���պ���ָ��)
    BTNode() {
        parent = nullptr;
        child.insert(0, nullptr);
    }
    explicit BTNode(T e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr) {
        parent = nullptr;                 //��Ϊ���ڵ�,���ҳ�ʼʱ
        key.insert(0, e);                 //ֻ��һ���ؼ���,�Լ�
        child.insert(0, lc);              //��������
        child.insert(1, rc);
        if (lc) {
            lc->parent = this;
        }
        if (rc) {
            rc->parent = this;
        }
    }
};


template<typename T> //B-��ģ����
class BTree {
protected:
    int _size;       //��Źؼ��������
    int _order;      //B-���Ľ״�,����Ϊ��(����ʱָ��,һ�㲻���޸�)
    BTNodePosi(T) _root;  //���ڵ�
    BTNodePosi(T) _hot;   //search���������ʵķǿ�(����Ϊ����)�Ľڵ�λ��
    void solveOverflow (BTNodePosi(T));           //����������֮��ķ��Ѵ���
    void solveUnderflow (BTNodePosi(T));          //��ɾ��������֮��ĺϲ�����
public:
    explicit BTree(int order = 3) : _order(order), _size(0) { //���캯��(Ĭ�����Ϊ����)
        _root = new BTNode<T>();
    }
    ~BTree() {                                                //��������(�ͷ����еĽڵ�)
        delete _root;
    }
    int order() const {                 //�״�
        return _order;
    };
    int size() const {                  //��ģ
        return _size;
    }
    BTNodePosi(T)& root() {             //���ڵ�
        return _root;
    }
    bool empty() const {                //�п�
        return !_root;
    }
    BTNodePosi(T) search(const T& e);   //����
    bool insert(const T& e);            //����
    bool remove(const T& e);            //ɾ��
};


#endif //DATASTRUCTURE_BSUBTREE_H

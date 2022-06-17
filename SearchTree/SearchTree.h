//
// Created by wjy on 22-6-17.
//

#ifndef SEARCHTREE_SEARCHTREE_H
#define SEARCHTREE_SEARCHTREE_H

#include "../BinaryTree/BinTree.h"


//����ģ����
template<typename K, typename V>
struct Entry{
    K key;              //�ؼ���
    V value;            //��ֵ
    Entry(K k = K(), V v = V()) : key(k), value(v) {}     //Ĭ�Ϲ��캯��
    Entry(Entry<K,V> const& e) : key(e.key), value(e.value) {} //���ڿ�¡�Ĺ��캯��
    bool operator< (Entry<K,V> const& e) {           //�Ƚ���
        return key < e.key;
    }
    bool operator> (Entry<K,V> const& e) {
        return key > e.key;
    }
    bool operator== (Entry<K,V> const& e) {
        return key == e.key;
    }
    bool operator!= (Entry<K,V> const& e) {
        return key == e.key;
    }
}; //�����ڱȽ������е���,�Ӵ��������ϸ����ִ��������Ӧ�Ĺؼ���

//��BinTree����BSTģ����
template<typename T>
class BST : public BinTree<T> {
protected:
    BinNodePosi(T) _hot;              //"����"�ڵ�ĸ���
    BinNodePosi(T) connect34 (        //����"3 + 4"�ṹ,����3���ڵ��Լ��Ŀ�����
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T)
            );
    BinNodePosi(T) rotateAt (BinNodePosi(T) x); //��x���丸��,�游��ͳһ��ת����
public:                               //�����ӿ�:��virtual����,ǿ��Ҫ������������(BST����)���ݸ��ԵĹ�����д
    virtual BinNodePosi(T)& search(const T& e);  //����
    virtual BinNodePosi(T) insert(const T& e);   //����
    virtual bool remove(const T& e);             //ɾ��
};



#endif //SEARCHTREE_SEARCHTREE_H

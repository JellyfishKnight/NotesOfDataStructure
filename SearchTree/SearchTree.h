//
// Created by wjy on 22-6-17.
//

#ifndef SEARCHTREE_SEARCHTREE_H
#define SEARCHTREE_SEARCHTREE_H

#include "../BinaryTree/BinTree.h"


//词条模板类
template<typename K, typename V>
struct Entry{
    K key;              //关键字
    V value;            //数值
    Entry(K k = K(), V v = V()) : key(k), value(v) {}     //默认构造函数
    Entry(Entry<K,V> const& e) : key(e.key), value(e.value) {} //基于克隆的构造函数
    bool operator< (Entry<K,V> const& e) {           //比较器
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
}; //得益于比较器和判等器,从此往后不再严格区分词条及其对应的关键码

//由BinTree派生BST模板类
template<typename T>
class BST : public BinTree<T> {
protected:
    BinNodePosi(T) _hot;              //"命中"节点的父亲
    BinNodePosi(T) connect34 (        //按照"3 + 4"结构,联接3个节点以及四棵子树
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T)
            );
    BinNodePosi(T) rotateAt (BinNodePosi(T) x); //对x及其父亲,祖父做统一旋转调整
public:                               //基本接口:用virtual修饰,强制要求所有派生类(BST变种)根据各自的规则重写
    virtual BinNodePosi(T)& search(const T& e);  //查找
    virtual BinNodePosi(T) insert(const T& e);   //插入
    virtual bool remove(const T& e);             //删除
};



#endif //SEARCHTREE_SEARCHTREE_H

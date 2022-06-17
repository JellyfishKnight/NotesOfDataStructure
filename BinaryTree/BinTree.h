//
// Created by wjy on 22-6-12.
//

#ifndef BINARYTREE_BINTREE_H
#define BINARYTREE_BINTREE_H

#include "BinNode.h"
#include "stack"


template<typename T>         //二叉树模板类
class BinTree {
protected:
    int _size;                   //规模
    BinNodePosi(T) _root;        //根节点
    virtual int updateHeight(BinNodePosi(T) x);      //更新节点x的高度
    void updateHeightAbove(BinNodePosi(T) x);        //更新节点x及其祖先的高度
public:
    BinTree() : _size(0), _root(nullptr) {}          //构造函数
    ~BinTree() {                                     //析构函数
        if (0 < _size) {
            remove(_root);
        }
    }
    int size() const {               //规模
        return _size;
    }
    bool empty() const {             //判空
        return !_root;
    }
    BinNodePosi(T) root() const {    //树根
        return _root;
    }
    BinNodePosi(T) insertAsRoot (T const& e);                    //插入根节点
    BinNodePosi(T) insertAsLC (BinNodePosi(T) x, T const& e);    //e作为x的左孩子插入
    BinNodePosi(T) insertAsRC (BinNodePosi(T) x, T const& e);    //e作为x的右孩子插入
    BinNodePosi(T) attachAsLC (BinNodePosi(T) x, BinTree<T>* &tree);   //tree作为x的左子树接入
    BinNodePosi(T) attachAsRC (BinNodePosi(T) x, BinTree<T>* &tree);   //tree作为x的右子树接入
    int remove (BinNodePosi(T) x);          //删除以位置x处节点为根的子树,返回该子树原先的规模
    BinTree<T>* secede (BinNodePosi(T) x);  //将子树x从当前树中删除,并将其转换为一颗独立子树
    template<typename VST>
    void travLevel (VST& visit) {           //层次遍历
        if (_root) {
            _root->template travLevel(visit);
        }
    }
    template<typename VST>
    void travPre (VST& visit) {             //先序便利
        if (_root) {
            travPre_I(_root, visit);
        }
    }
    template<typename VST>
    void travIn (VST& visit) {              //中序遍历
        if (_root) {
            travIn_I3(_root, visit);
        }
    }
    template<typename VST>
    void travPost (VST& visit) {            //后续遍历
        if (_root) {
            travPost_I(_root, visit);
        }
    }
    //比较器
    bool operator< (BinTree<T> const& t) {
        return _root && t._root && _root < t._root;
    }
    bool operator== (BinTree<T> const& t) {
        return _root && t._root && _root == t._root;
    }
    bool operator!= (BinTree<T> const& t) {
        return _root && t._root && _root != t._root;
    }
    bool operator> (BinTree<T> const& t) {
        return _root && t._root && _root > t._root;
    }
    bool operator>= (BinTree<T> const& t) {
        return _root && t._root && _root >= t._root;
    }
    bool operator<= (BinTree<T> const& t) {
        return _root && t._root && _root <= t._root;
    }
};






#endif //BINARYTREE_BINTREE_H

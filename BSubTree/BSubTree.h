//
// Created by wjy on 22-6-28.
//

#ifndef DATASTRUCTURE_BSUBTREE_H
#define DATASTRUCTURE_BSUBTREE_H

#include "../Vector/Vector.h"

#define BTNodePosi(T) BTNode<T>*         //B-树节点位置

template<typename T>                     //B-树节点模板类
struct BTNode {
//成员(为简化描述统一开放)
    BTNodePosi(T) parent;                //父节点
    Vector<T> key;                       //关键码变量
    Vector<BTNodePosi(T)> child;         //孩子变量(其长度总比key多一)
//构造函数(注意:BTNode只能作为根节点创建,而且初始时有0个关键码和1个空孩子指针)
    BTNode() {
        parent = nullptr;
        child.insert(0, nullptr);
    }
    explicit BTNode(T e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr) {
        parent = nullptr;                 //作为根节点,并且初始时
        key.insert(0, e);                 //只有一个关键码,以及
        child.insert(0, lc);              //两个孩子
        child.insert(1, rc);
        if (lc) {
            lc->parent = this;
        }
        if (rc) {
            rc->parent = this;
        }
    }
};


template<typename T> //B-树模板类
class BTree {
protected:
    int _size;       //存放关键码的总数
    int _order;      //B-树的阶次,至少为三(创建时指定,一般不能修改)
    BTNodePosi(T) _root;  //根节点
    BTNodePosi(T) _hot;   //search函数最后访问的非空(除非为空树)的节点位置
    void solveOverflow (BTNodePosi(T));           //因插入而上溢之后的分裂处理
    void solveUnderflow (BTNodePosi(T));          //因删除而下溢之后的合并处理
public:
    explicit BTree(int order = 3) : _order(order), _size(0) { //构造函数(默认最低为三阶)
        _root = new BTNode<T>();
    }
    ~BTree() {                                                //析构函数(释放所有的节点)
        delete _root;
    }
    int order() const {                 //阶次
        return _order;
    };
    int size() const {                  //规模
        return _size;
    }
    BTNodePosi(T)& root() {             //根节点
        return _root;
    }
    bool empty() const {                //判空
        return !_root;
    }
    BTNodePosi(T) search(const T& e);   //查找
    bool insert(const T& e);            //插入
    bool remove(const T& e);            //删除
};


#endif //DATASTRUCTURE_BSUBTREE_H

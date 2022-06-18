//
// Created by wjy on 22-6-17.
//

#ifndef DATASTRUCTURE_AVLTREE_H
#define DATASTRUCTURE_AVLTREE_H

#include "../SearchTree/SearchTree.h"
#define Balanced(x) (stature((x).lc) == stature((x).rc))               //理想平衡条件
#define BalFac(x) (stature((x).lc) - stature((x).rc))                  //平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))              //AVL平衡条件

/*************************************************
 * 在左,右孩子中取更高者
 * 在AVL平衡调整前,借此确定重构方案
 *************************************************/
#define tallerChild(x) ( \
    stature((x)->lc) > stature((x)->rc) ? (x)->lc : ( /*左高*/ \
    stature((x)->lc) < stature((x)->rc) ? (x)->rc : ( /*右高*/ \
    IsLChild(*(x)) ? (x)->lc : (x)->rc                /*等高:与父亲x同侧者(zIg-zIg)或(zAg-zAg)优先*/ \
    )                    \
    )                    \
    )




template<typename T> //基于BST实现AVL树
class AVLTree :public BST<T> { //由BST派生AVL模板类
public:
    BinNodePosi(T) insert (const T& e); //插入(重写)
    bool remove(const T& e);            //删除(重写)
//BST::search()等其余接口可直接沿用
};









#endif //DATASTRUCTURE_AVLTREE_H

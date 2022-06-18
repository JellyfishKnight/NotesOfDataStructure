//
// Created by wjy on 22-6-17.
//

#ifndef DATASTRUCTURE_AVLTREE_H
#define DATASTRUCTURE_AVLTREE_H

#include "../SearchTree/SearchTree.h"
#define Balanced(x) (stature((x).lc) == stature((x).rc))               //����ƽ������
#define BalFac(x) (stature((x).lc) - stature((x).rc))                  //ƽ������
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))              //AVLƽ������

/*************************************************
 * ����,�Һ�����ȡ������
 * ��AVLƽ�����ǰ,���ȷ���ع�����
 *************************************************/
#define tallerChild(x) ( \
    stature((x)->lc) > stature((x)->rc) ? (x)->lc : ( /*���*/ \
    stature((x)->lc) < stature((x)->rc) ? (x)->rc : ( /*�Ҹ�*/ \
    IsLChild(*(x)) ? (x)->lc : (x)->rc                /*�ȸ�:�븸��xͬ����(zIg-zIg)��(zAg-zAg)����*/ \
    )                    \
    )                    \
    )




template<typename T> //����BSTʵ��AVL��
class AVLTree :public BST<T> { //��BST����AVLģ����
public:
    BinNodePosi(T) insert (const T& e); //����(��д)
    bool remove(const T& e);            //ɾ��(��д)
//BST::search()������ӿڿ�ֱ������
};









#endif //DATASTRUCTURE_AVLTREE_H

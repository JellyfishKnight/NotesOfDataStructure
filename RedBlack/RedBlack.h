//
// Created by wjy on 22-7-2.
//

#ifndef DATASTRUCTURE_REDBLACK_H
#define DATASTRUCTURE_REDBLACK_H

#include "../SearchTree/SearchTree.h"

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ( /*RedBlack�߶ȸ�������*/\
(stature((x).lc) == stature((x).rc)) && \
((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)) \
)



template<typename T> //����BSTʵ�ֺ����
class RedBlack : public BST<T>{ //RedBlackģ����
protected:
    void solveDoubleRed(BinNodePosi(T) x);   //˫������
    void solveDoubleBlack(BinNodePosi(T) x); //˫������
    int updateHeight(BinNodePosi(T) x);      //���½ڵ�x�ĸ߶�
public:
    BinNodePosi(T) insert(const T& e);       //����
    bool remove(const T& e);                 //ɾ��
//����ӿڿ�ֱ������
};


#endif //DATASTRUCTURE_REDBLACK_H

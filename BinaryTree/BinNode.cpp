//
// Created by wjy on 22-6-17.
//

/**
 * @brief 以下两个插入函数默认节点尚且无左右孩子
 */
#include "BinNode.h"

template<typename T>
BinNode<T> *BinNode<T>::insertAsLC(const T &e) {
    return lc = new BinNode(e, this);          //将e作为当前节点的左孩子插入二叉树
}

template<typename T>
BinNode<T> *BinNode<T>::insertAsRC(const T &e) {
    return rc = new BinNode(e, this);          //将e作为当前节点的右孩子插入二叉树
}

template<typename T>      //定位节点v的直接后继
BinNode<T> *BinNode<T>::succ() {
    BinNodePosi(T) s = this;                   //记录后继的临时变量
    if (rc) {             //若有有孩子,则直接后继必在右子树中
        s = rc;
        while (HasLChild(*s)) {                //最靠左(最小)的节点
            s = s->lc;
        }
    } else {              //否则,直接后继应该是"将当前节点包含于其左子树中的最低祖先"
        while (IsRChild(*s)) {         //逆向地沿右向分支,不断朝左上方移动
            s = s->parent;
        }
        s = s->parent;    //最后再朝右上方移动一步,即抵达直(如果存在)
    }
    return s;
}

/**
 * @brief 以下函数是层次遍历(广度优先遍历)
 */
template<typename T> template<typename VST> //元素类型,操作器
void BinNode<T>::travLevel(VST &visit) {    //二叉树层次遍历算法
    Queue<BinNodePosi(T)> q;                //辅助队列
    q.enqueue(this);                     //根节点入队
    while (!q.empty()) {                    //在队列再次变空之前,反复迭代
        BinNodePosi(T) x = q.dequeue();     //取出队首节点并访问之
        visit(x->data);
        if (HasLChild(*x)) {                //左孩子入队
            q.enqueue(x->lc);
        }
        if (HasRChild(*x)) {                //右孩子入队
            q.enqueue(x->rc);
        }
    }
}


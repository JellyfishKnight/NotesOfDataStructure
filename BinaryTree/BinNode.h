//
// Created by wjy on 22-6-12.
//

#ifndef BINARYTREE_BINNODE_H
#define BINARYTREE_BINNODE_H

#include <cstdlib>
#include "../Queue/Queue.h"


#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)
typedef enum {RB_RED, RB_BLACK} RBCOLOR;

template<typename T>
struct BinNode{
//数据成员(为简化描述统一开放,可自行封装)
    T data;                      //数值
    BinNodePosi(T) parent;       //父节点
    BinNodePosi(T) lc;           //左孩子
    BinNodePosi(T) rc;           //右孩子
    int height;                  //高度(通用)
    int npl;                   //Null Path Length (左式堆,也可以直接用height代替)
    RBCOLOR color;               //颜色(红黑树)
//构造函数
    BinNode() : parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RB_RED) {}
    BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) l = nullptr, BinNodePosi(T) r = nullptr,
        int h = 0, int n = 1, RBCOLOR c = RB_RED) :
        data(e), parent(p), lc(l), rc(r), height(h), npl(n), color(c) {}
//操作接口
    int size();                       //统计当前节点后代总数,亦即以其为根的子树的规模
    BinNodePosi(T) insertAsLC(T const&);    //作为当前节点的左孩子插入
    BinNodePosi(T) insertAsRC(T const&);    //作为当前节点的右孩子插入
    BinNodePosi(T) succ();                    //作为当前节点的直接后继
    template<typename VST>            //子树层次遍历
    void travLevel (VST&);
//    template<typename VST>            //子树先序遍历
//    void travPre (VST&);
//    template<typename VST>            //子树中序遍历
//    void travIn (VST&);
//    template<typename VST>            //子树后序遍历
//    void travPost (VST&);
//比较器,判等器
    bool operator<(BinNode<T> const& bn) {
        return data < bn.data;
    }
    bool operator==(BinNode<T> const& bn) {
        return data == bn.data;
    }
    bool operator>(BinNode<T> const& bn) {
        return data > bn.data;
    }
    bool operator>=(BinNode<T> const& bn) {
        return data >= bn.data;
    }
    bool operator<=(BinNode<T> const& bn) {
        return data <= bn.data;
    }
    bool operator!=(BinNode<T> const& bn) {
        return data != bn.data;
    }
};


/**********************************************************************
* BinNode状态与性质的判断
**********************************************************************/
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (& (x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (& (x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
//至少用有一个孩子
#define HasChild(x) (HasLChild(x) || HasRChild(x))
//同时拥有两个孩子
#define HasBothChild(x) (HasRChild(x) && HasLChild(x))   //同时有两个孩子
#define IsLeaf(x) (!HasChild(x))



/**********************************************************************
* 与BinNode具有特定关系的节点及指针
**********************************************************************/
//兄弟
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
//叔叔
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
//来自父亲的引用
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))



/**
 * @brief 以下两个插入函数默认节点尚且无左右孩子
 */
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






#endif //BINARYTREE_BINNODE_H

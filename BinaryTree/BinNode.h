//
// Created by wjy on 22-6-12.
//

#ifndef BINARYTREE_BINNODE_H
#define BINARYTREE_BINNODE_H

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
    BinNodePosi(T) succ;                    //作为当前节点的直接后继
    template<typename VST>            //子树层次遍历
    void travLevel (VST&);
    template<typename VST>            //子树先序遍历
    void travPre (VST&);
    template<typename VST>            //子树中序遍历
    void travIn (VST&);
    template<typename VST>            //子树后序遍历
    void travPost (VST&);
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

#endif //BINARYTREE_BINNODE_H

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
            travPre(_root, visit);
        }
    }
    template<typename VST>
    void travIn (VST& visit) {              //中序遍历
        if (_root) {
            travIn(_root, visit);
        }
    }
    template<typename VST>
    void travPost (VST& visit) {            //后续遍历
        if (_root) {
            travPost(_root, visit);
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

template<typename T>
int BinTree<T>::updateHeight(BinNode<T> *x) {          //更新节点x高度
    return x->height = 1 + max (stature(x->lc), stature(x->rc));   //具体规则因树而异
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> *x) {    //更新高度
    while (x) {                                        //从x出发覆盖历代祖先,可优化
        updateHeight(x);
        x = x->parent;
    }
}

template<typename T>              //将e作为根节点插入空的二叉树
BinNode<T> *BinTree<T>::insertAsRoot(const T &e) {
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T>              //将e作为x的左孩子插入
BinNode<T> *BinTree<T>::insertAsLC(BinNode<T> *x, const T &e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template<typename T>              //将e作为x的右孩子插入
BinNode<T> *BinTree<T>::insertAsRC(BinNode<T> *x, const T &e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template<typename T>        //二叉树子树接入算法:将tree作为x的左子树接入,tree本身置空
BinNode<T> *BinTree<T>::attachAsLC(BinNode<T> *x, BinTree<T> *&tree) {
    if (x->lc = tree->_root) {       //接入
        x->lc->parent = x;
    }
    _size += tree->_size;        //更新全树的规模与x所有祖先的高度
    updateHeightAbove(x);
    tree->_root = nullptr;       //释放原树,返回接入位置
    tree->_size = 0;
    release(tree);
    tree = nullptr;
    return x;
}

template<typename T>        //二叉树子树接入算法:将tree作为x的右子树接入,tree本身置空
BinNode<T> *BinTree<T>::attachAsRC(BinNode<T> *x, BinTree<T> *&tree) {
    if (x->rc = tree->_root) {      //接入
        x->rc->parent = x;
    }
    _size += tree->_size;           //更新全树的规模以及x所有祖先的高度
    updateHeightAbove(x);
    tree->_root = nullptr;          //释放原树,返回接入位置
    tree->_size = 0;
    release(tree);
    tree = nullptr;
    return x;
}

template<typename T>                //删除二叉树中位置x处的节点及其后代,返回被删除节点的位置
int BinTree<T>::remove(BinNode<T> *x) {     //x要为二叉树中的合法位置
    FromParentTo(*x) = nullptr;             //切断来自父节点的指针
    updateHeightAbove(x->parent);        //更新祖先高度
    int n = removeAt(x);                    //删除子树x,更新规模,返回删除节点的总数
    _size -= n;
    return n;
}

template<typename T>                //删除二叉树中位置x处的节点及其后代,返回被删除节点的数值
static int removeAt (BinNodePosi(T) x) {    //x要为二叉树中的合法位置
    if (!x) {                       //递归,空树
        return 0;
    }
    int n = 1 + removeAt (x->lc) + removeAt(x->rc);  //递归释放左右子树
    release(x->data);               //释放被摘除节点,并返回删除节点总数
    release(x);
    return n;
}

template<typename T>          //二叉树的子树分离算法:将子树x从当前树摘除,将其封装为一颗独立子树返回
BinTree<T> *BinTree<T>::secede(BinNode<T> *x) {      //x要为二叉树中合法位置
    FromParentTo(*x) = nullptr;            //切断来自父节点的指针
    updateHeightAbove(x->parent);       //更新原树中所有祖先的高度
    BinTree<T>* s = new BinTree<T>;        //新树以x为根
    s->_root = x;
    x->parent = nullptr;
    s->_size = x->size();                  //更新规模,返回分离出来的子树
    _size -= s->_size;
    return s;
}

/**
 * @brief 以下函数介绍递归式遍历
 */
template<typename T, typename VST> //元素类型,操作器
void travPre_R (BinNodePosi(T) x, VST& visit) { //二叉树先序遍历算法(递归版)
    if (!x) {
        return ;
    }
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template<typename T, typename VST> //元素类型,操作器
void travPost_R (BinNodePosi(T) x, VST& visit) { //二叉树后续遍历算法(递归版)
    if (!x) {
        return ;
    }
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template<typename T, typename VST> //元素类型,操作器
void travIn_R (BinNodePosi(T) x, VST& visit) { //二叉树中序遍历算法(递归版)
    if (!x) {
        return ;
    }
    travIn_R(x->lc);
    visit(x->data);
    travIn_R(x->rc);
}

/**
 * @brief 以下几个函数为迭代实现遍历
 */
template<typename T, typename VST>       //元素类型,操作器
static void visitAlongLeftBranch (BinNodePosi(T) x, VST& visit, std::stack<BinNodePosi(T)>& s) {
    while (x) {
        visit (x->data);                 //访问当前节点
        if (!x->rc) {
            s.push(x->rc);               //将右孩子入栈暂存
        }
        x = x->lc;                       //沿左分支深入一层
    }
}

template<typename T, typename VST>       //元素类型,操作器
void travPre_I (BinNodePosi(T) x, VST& visit) { //二叉树先序遍历算法(迭代版)
    std::stack<BinNodePosi(T)> s;        //辅助栈
    while (true) {
        visitAlongLeftBranch(x, visit, s);  //从当前节点出发,逐批访问
        if (s.empty()) {                 //直到栈空
            break;
        }
        x = s.top();                     //弹出下一批的起点
        s.pop();
    }
}

template<typename T>    //从当前节点出发,沿左分支不断深入,直至叶节点
static void goAlongLeftBranch(BinNodePosi(T) x, std::stack<BinNodePosi(T)>& s) {
    while (x) {         //当前节点入栈后随机向左侧分支深入,迭代直到叶节点
        s.push(x);
        x = x->lc;
    }
}

template<typename T, typename VST>       //元素类型,操作器
void travIn_I (BinNodePosi(T) x, VST& visit) {  //二叉树中序遍历算法(迭代版)
    std::stack<BinNodePosi(T)> s;        //辅助栈
    while (true) {
        goAlongLeftBranch(x, s);      //从当前节点出发,逐批入栈
        if (s.empty()) {                 //直到所有节点处理完毕
            break;
        }
        x = s.top();                     //弹出栈顶节点并访问之
        s.pop();
        visit(x->data);
        x = x->rc;                       //转向右子树
    }
}

template<typename T, typename VST>       //元素类型,操作器
void travIn_I2 (BinNodePosi(T) x, VST& visit) { //二叉树中序遍历算法(迭代办2版)
    std::stack<BinNodePosi(T)> s;        //辅助栈
    while (true) {
        if (x) {
            s.push(x);                   //根节点入栈
            x = x->lc;                   //深入遍历左子树
        } else if (!s.empty()) {
            x = s.top();                 //尚未访问的最低祖先出栈
            s.pop();
            visit(x->data);              //访问节点
            x = x->rc;                   //遍历祖先的右子树
        } else {
            break;                       //遍历完成
        }
    }
}








#endif //BINARYTREE_BINTREE_H

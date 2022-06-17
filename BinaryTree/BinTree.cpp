//
// Created by wjy on 22-6-17.
//
#include "BinTree.h"


template<typename T>
int BinTree<T>::updateHeight(BinNode<T> *x) {          //���½ڵ�x�߶�
    return x->height = 1 + max (stature(x->lc), stature(x->rc));   //���������������
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> *x) {    //���¸߶�
    while (x) {                                        //��x����������������,���Ż�
        updateHeight(x);
        x = x->parent;
    }
}

template<typename T>              //��e��Ϊ���ڵ����յĶ�����
BinNode<T> *BinTree<T>::insertAsRoot(const T &e) {
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T>              //��e��Ϊx�����Ӳ���
BinNode<T> *BinTree<T>::insertAsLC(BinNode<T> *x, const T &e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template<typename T>              //��e��Ϊx���Һ��Ӳ���
BinNode<T> *BinTree<T>::insertAsRC(BinNode<T> *x, const T &e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template<typename T>        //���������������㷨:��tree��Ϊx������������,tree�����ÿ�
BinNode<T> *BinTree<T>::attachAsLC(BinNode<T> *x, BinTree<T> *&tree) {
    if (x->lc = tree->_root) {       //����
        x->lc->parent = x;
    }
    _size += tree->_size;        //����ȫ���Ĺ�ģ��x�������ȵĸ߶�
    updateHeightAbove(x);
    tree->_root = nullptr;       //�ͷ�ԭ��,���ؽ���λ��
    tree->_size = 0;
    release(tree);
    tree = nullptr;
    return x;
}

template<typename T>        //���������������㷨:��tree��Ϊx������������,tree�����ÿ�
BinNode<T> *BinTree<T>::attachAsRC(BinNode<T> *x, BinTree<T> *&tree) {
    if (x->rc = tree->_root) {      //����
        x->rc->parent = x;
    }
    _size += tree->_size;           //����ȫ���Ĺ�ģ�Լ�x�������ȵĸ߶�
    updateHeightAbove(x);
    tree->_root = nullptr;          //�ͷ�ԭ��,���ؽ���λ��
    tree->_size = 0;
    release(tree);
    tree = nullptr;
    return x;
}

template<typename T>                //ɾ����������λ��x���Ľڵ㼰����,���ر�ɾ���ڵ��λ��
int BinTree<T>::remove(BinNode<T> *x) {     //xҪΪ�������еĺϷ�λ��
    FromParentTo(*x) = nullptr;             //�ж����Ը��ڵ��ָ��
    updateHeightAbove(x->parent);        //�������ȸ߶�
    int n = removeAt(x);                    //ɾ������x,���¹�ģ,����ɾ���ڵ������
    _size -= n;
    return n;
}

template<typename T>                //ɾ����������λ��x���Ľڵ㼰����,���ر�ɾ���ڵ����ֵ
static int removeAt (BinNodePosi(T) x) {    //xҪΪ�������еĺϷ�λ��
    if (!x) {                       //�ݹ�,����
        return 0;
    }
    int n = 1 + removeAt (x->lc) + removeAt(x->rc);  //�ݹ��ͷ���������
    release(x->data);               //�ͷű�ժ���ڵ�,������ɾ���ڵ�����
    release(x);
    return n;
}

template<typename T>          //�����������������㷨:������x�ӵ�ǰ��ժ��,�����װΪһ�Ŷ�����������
BinTree<T> *BinTree<T>::secede(BinNode<T> *x) {      //xҪΪ�������кϷ�λ��
    FromParentTo(*x) = nullptr;            //�ж����Ը��ڵ��ָ��
    updateHeightAbove(x->parent);       //����ԭ�����������ȵĸ߶�
    auto* s = new BinTree<T>;        //������xΪ��
    s->_root = x;
    x->parent = nullptr;
    s->_size = x->size();                  //���¹�ģ,���ط������������
    _size -= s->_size;
    return s;
}

/**
 * @brief ���º������ܵݹ�ʽ����
 */
template<typename T, typename VST> //Ԫ������,������
void travPre_R (BinNodePosi(T) x, VST& visit) { //��������������㷨(�ݹ��)
    if (!x) {
        return ;
    }
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template<typename T, typename VST> //Ԫ������,������
void travPost_R (BinNodePosi(T) x, VST& visit) { //���������������㷨(�ݹ��)
    if (!x) {
        return ;
    }
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template<typename T, typename VST> //Ԫ������,������
void travIn_R (BinNodePosi(T) x, VST& visit) { //��������������㷨(�ݹ��)
    if (!x) {
        return ;
    }
    travIn_R(x->lc);
    visit(x->data);
    travIn_R(x->rc);
}

/**
 * @brief ���¼�������Ϊ����ʵ�ֱ���
 */
template<typename T, typename VST>       //Ԫ������,������
static void visitAlongLeftBranch (BinNodePosi(T) x, VST& visit, std::stack<BinNodePosi(T)>& s) {
    while (x) {
        visit (x->data);                 //���ʵ�ǰ�ڵ�
        if (!x->rc) {
            s.push(x->rc);               //���Һ�����ջ�ݴ�
        }
        x = x->lc;                       //�����֧����һ��
    }
}

template<typename T, typename VST>       //Ԫ������,������
void travPre_I (BinNodePosi(T) x, VST& visit) { //��������������㷨(������)
    std::stack<BinNodePosi(T)> s;        //����ջ
    while (true) {
        visitAlongLeftBranch(x, visit, s);  //�ӵ�ǰ�ڵ����,��������
        if (s.empty()) {                 //ֱ��ջ��
            break;
        }
        x = s.top();                     //������һ�������
        s.pop();
    }
}

template<typename T>    //�ӵ�ǰ�ڵ����,�����֧��������,ֱ��Ҷ�ڵ�
static void goAlongLeftBranch(BinNodePosi(T) x, std::stack<BinNodePosi(T)>& s) {
    while (x) {         //��ǰ�ڵ���ջ�����������֧����,����ֱ��Ҷ�ڵ�
        s.push(x);
        x = x->lc;
    }
}

template<typename T, typename VST>       //Ԫ������,������
void travIn_I (BinNodePosi(T) x, VST& visit) {  //��������������㷨(������)
    std::stack<BinNodePosi(T)> s;        //����ջ
    while (true) {
        goAlongLeftBranch(x, s);      //�ӵ�ǰ�ڵ����,������ջ
        if (s.empty()) {                 //ֱ�����нڵ㴦�����
            break;
        }
        x = s.top();                     //����ջ���ڵ㲢����֮
        s.pop();
        visit(x->data);
        x = x->rc;                       //ת��������
    }
}

template<typename T, typename VST>       //Ԫ������,������
void travIn_I2 (BinNodePosi(T) x, VST& visit) { //��������������㷨(������2��)
    std::stack<BinNodePosi(T)> s;        //����ջ
    while (true) {
        if (x) {
            s.push(x);                   //���ڵ���ջ
            x = x->lc;                   //�������������
        } else if (!s.empty()) {
            x = s.top();                 //��δ���ʵ�������ȳ�ջ
            s.pop();
            visit(x->data);              //���ʽڵ�
            x = x->rc;                   //�������ȵ�������
        } else {
            break;                       //�������
        }
    }
}

template<typename T, typename VST>       //Ԫ������,������
void travIn_I3 (BinNodePosi(T) x, VST& visit) { //�������������(������3��)
    bool backtrack = false;              //ǰһ���Ƿ�մ�����������--ʡȥջ,��O(1)ʱ��
    while (true) {
        if (!backtrack && HasLChild(*x)) {      //�����������Ҳ��Ǹոջ���,��
            x = x->lc;                   //�������������
        } else {                         //����--����������ոջ���(�൱����������)
            visit(x->data);              //���ʸýڵ�
            if (HasRChild(*x)) {         //����������Ϊ�ǿ�,��
                x = x->rc;               //��������������
                backtrack = false;       //�رջ��ݱ�־
            } else {                     //����������,��
                if (!(x = x->succ())) {  //����(���ִ�ĩ�ڵ�ʱ���˳�����)
                    break;
                }
                backtrack = true;        //�����û��ݱ�־
            }
        }
    }
}



/**
 * @brief ���¼�������Ϊʵ�ֺ�������ĵ�����
 */
template<typename T>      //����sջ���ڵ�Ϊ����������,�ҵ�������ɼ�Ҷ�ڵ�
static void gotoHLVFL (std::stack<BinNodePosi(T)>& s) { //��;�������ڵ�������ջ
    while (BinNodePosi(T) x = s.top()) {      //�Զ�����,������鵱ǰ�ڵ�(��ջ��)
        if (HasLChild(*x)) {                  //����������
            if (HasRChild(*x)) {              //�����Һ���,������ջ
                s.push(x->rc);
            }
            s.push(x->lc);                    //Ȼ���ת������
        } else {                              //ʵ������
            s.push(x->rc);                    //������
        }
    }
    s.pop();                                  //����֮ǰ,����ջ���Ŀսڵ�
}

template<typename T, typename VST>
void travPost_I (BinNodePosi(T) x, VST& visit) { //�������ĺ������(������)
    std::stack<BinNodePosi(T)> s;             //����ջ
    if (x) {                                  //���ڵ���ջ
        s.push(x);
    }
    while (!s.empty()) {
        if (s.top() != x->parent) {           //��ջ���ǵ�ǰ�ڵ�֮��(���Ϊ������),��ʱ��
            gotoHLVFL(s);                  //����������Ϊ��֮������,�ҵ�HLVFL(�൱��ݹ���������)
        }
        x = s.top();                          //����ջ��(��ǰһ�ڵ�֮���),������֮
        s.pop();
        visit(x->data);
    }
}



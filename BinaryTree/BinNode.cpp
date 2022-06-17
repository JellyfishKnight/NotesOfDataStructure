//
// Created by wjy on 22-6-17.
//

/**
 * @brief �����������뺯��Ĭ�Ͻڵ����������Һ���
 */
#include "BinNode.h"

template<typename T>
BinNode<T> *BinNode<T>::insertAsLC(const T &e) {
    return lc = new BinNode(e, this);          //��e��Ϊ��ǰ�ڵ�����Ӳ��������
}

template<typename T>
BinNode<T> *BinNode<T>::insertAsRC(const T &e) {
    return rc = new BinNode(e, this);          //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������
}

template<typename T>      //��λ�ڵ�v��ֱ�Ӻ��
BinNode<T> *BinNode<T>::succ() {
    BinNodePosi(T) s = this;                   //��¼��̵���ʱ����
    if (rc) {             //�����к���,��ֱ�Ӻ�̱�����������
        s = rc;
        while (HasLChild(*s)) {                //���(��С)�Ľڵ�
            s = s->lc;
        }
    } else {              //����,ֱ�Ӻ��Ӧ����"����ǰ�ڵ���������������е��������"
        while (IsRChild(*s)) {         //������������֧,���ϳ����Ϸ��ƶ�
            s = s->parent;
        }
        s = s->parent;    //����ٳ����Ϸ��ƶ�һ��,���ִ�ֱ(�������)
    }
    return s;
}

/**
 * @brief ���º����ǲ�α���(������ȱ���)
 */
template<typename T> template<typename VST> //Ԫ������,������
void BinNode<T>::travLevel(VST &visit) {    //��������α����㷨
    Queue<BinNodePosi(T)> q;                //��������
    q.enqueue(this);                     //���ڵ����
    while (!q.empty()) {                    //�ڶ����ٴα��֮ǰ,��������
        BinNodePosi(T) x = q.dequeue();     //ȡ�����׽ڵ㲢����֮
        visit(x->data);
        if (HasLChild(*x)) {                //�������
            q.enqueue(x->lc);
        }
        if (HasRChild(*x)) {                //�Һ������
            q.enqueue(x->rc);
        }
    }
}


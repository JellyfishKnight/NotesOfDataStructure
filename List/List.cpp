//
// Created by wjy on 22-6-17.
//

#include <cstdlib>
#include "List.h"
template<typename T>
void List<T>::init() {     //�б��ʼ��
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;                //��¼��С
}

template<typename T>    //�������б��ڽڵ�p��n��ǰ����,�ҵ�����e�������
ListNodePosi(T) List<T>::find(const T &e, int n, ListNodePosi(T) p) const {
    while (n-- > 0) {                  //��������
        if (e == p->pred->data) {
            return p->pred;
        }
        p = p->pred;
    }
    return nullptr;            //ʧ��ʱ���ؿ�ָ��
}

template<typename T>           //��e��Ϊ�׽ڵ����
ListNodePosi(T) List<T>::insertAsFirst(const T &e) {
    _size++;
    return header->insertAsSucc(e);
}

template<typename T>           //��e��Ϊĩ�ڵ����
ListNodePosi(T) List<T>::insertAsLast(const T &e) {
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>            //��e��Ϊp�ĺ�̲���
ListNode<T> *List<T>::insertA(ListNode<T> *p, const T &e) {
    _size++;
    return p->insertAsSucc(e);
}

template<typename T>            //��e��Ϊp��ǰ������
ListNode<T> *List<T>::insertB(ListNode<T> *p, const T &e) {
    _size++;
    return p->insertAsPred(e);
}

template<typename T>
ListNode<T> *ListNode<T>::insertAsPred(T const &e) {
    ListNodePosi(T) x = new ListNode<T> (e, pred, this);      //�����½ڵ�
    pred->succ = x;                                           //������������
    pred = x;
    return x;
}

template<typename T>
ListNode<T> *ListNode<T>::insertAsSucc(T const &e) {
    ListNodePosi(T) x = new ListNode<T> (e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

template<typename T>         //�б��ڲ�����:�����б�����λ��p���n��
void List<T>::copyNodes(ListNode<T> *p, int n) {          //p�Ϸ�,��������n-1�����̽ڵ�
    init();                  //����ͷ,β�ڱ��ڵ㲢�ҳ�ʼ��
    while (n--) {
        insertAsLast(p->data);
        p = p->succ;            //����p���n��������Ϊĩ�ڵ����
    }
}

template<typename T>         //�����б�����λ��p���n��
List<T>::List(ListNode<T> *p, int n) {
    copyNodes(p, n);
}

template<typename T>          //���帴���б�L
List<T>::List(const List<T> &L) {
    copyNodes(L.first(), L._size);
}

template<typename T>         //����L���Ե�r�����n��
List<T>::List(const List<T> &L, int r, int n) {
    copyNodes(L[r], n);
}

template<typename T>         //ɾ���Ϸ��ڵ�p,��������ֵ
T List<T>::remove(ListNode<T> *p) {
    T e = p->data;
    p->pred->succ = p->succ;        //����ǰ�����
    p->succ->pred = p->pred;
    delete p;                       //�ͷŽڵ�,���´�С
    _size--;
    return e;
}

template<typename T>
List<T>::~List() {           //�б�������
    clear();                 //����б�,�ͷ�ͷβ�ڱ��ڵ�
    delete header;
    delete trailer;
}

template<typename T>        //����б�
int List<T>::clear() {
    int oldsize = _size;
    while(_size > 0) {
        remove(header->succ);        //����ɾ���ڵ�,ֱ����Ϊ��
    }
    return oldsize;
}

template<typename T>         //�޳������б��е��ظ��ڵ�
int List<T>::deduplicate() {
    if (_size < 2) {         //ƽ���б����ظ�
        return 0;
    }
    int oldSize = _size;
    ListNodePosi(T) p = header;           //p���׽ڵ㿪ʼ
    int r = 0;
    while (trailer != (p = p->succ)) {        //����ֱ��ĩ�ڵ�
        ListNodePosi(T) q = find (p->data, r , p);         //��p��r��ǰ���в����ظ�
        q ? remove(q) : r++;               //����ȷ������ɾ��,�����ȼ�һ
    }
    return oldSize - _size;                   //�����б��С�仯��
}

template<typename T>                      //��������ָ����Ʊ���
void List<T>::traverse(void (*visit) (T &)) {
    for (ListNodePosi(T) p = header; p != trailer; p = p->succ) {
        visit (p->data);
    }
}

template<typename T>
template<typename VST>            //Ԫ������,������
void List<T>::traverse(VST &visit) {
    for (ListNodePosi(T) p = header; p != trailer; p = p->succ) {
        visit(p->data);
    }
}

template<typename T>             //�޳������б���ظ���
int List<T>::uniquifiy() {        //����ɾ���ظ�Ԫ��,Ч�ʸ���
    if (_size < 2) {
        return 0;
    }
    int oldSize = _size;
    ListNodePosi(T) p = first();
    ListNodePosi(T) q;
    while (trailer != (q = p->succ)) {
        if (p->data != q->data) {          //������,��ת����һ����
            p = q;
        } else {
            remove(q);                  //����ɾ������
        }
    }
    return oldSize - _size;                //�����б�仯��С
}

template<typename T>                      //�������б��ڽڵ�p��n��ǰ�����ҵ�������e�������
ListNode<T> *List<T>::search(const T &e, int n, ListNode<T> *p) const {
    while (n-- >= 0) {                    //����p�������b��ǰ��,������������Ƚ�
        p = p->pred;
        if (p->data <= e) {               //ֱ�����л�����ֵԽ����߷�ΧԽ��
            break;
        }
    }
    return p;                             //���ز�����ֹ��λ��
}                                  //ʧ��ʱ,�����������߽�(�п�����header)����ʹ��valid�����жϳɹ����

template<typename T>                      //�����ͳһ���
void List<T>::sort(ListNode<T> *p, int n) {
    switch (rand() % 3) {
        case 1:
            insertionSort(p, n);
            break;
        case 2:
            selectSort(p, n);
            break;
        default:
            mergeSort(p, n);
            break;
    }
}


template<typename T>                      //�б�Ĳ�������:����ʼλ��Ϊp��n��Ԫ������
void List<T>::insertionSort(ListNode<T> * p, int n) {
    for (int i = 0; i < n; i++) {         //��һΪ�����ڵ�
        insertA(search(p->data, i, p), p->data);
        p = p->succ;                      //ת����һ�ڵ�
        remove(p->pred);
    }
}

template<typename T>                       //�б��ѡ������:����ʼ��λ��p��n��Ԫ������
void List<T>::selectSort(ListNode<T> *p, int n ) {
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; i++) {          //����������Ϊ(head, tail)
        tail = tail->succ;
    }
    while (1 < n) {                        //�����ٻ�ʣ�����ڵ�֮ǰ,�ڴ�����������
        ListNodePosi(T) max = selectMax(head->succ, n);           //�ҳ������(����ʱ��������)
        insertB(tail, remove(max));                     //����ת�Ƶ����������ĩβ(��Ϊ���������µ�����Ԫ��)
        tail = tail->pred;
        n--;
    }
}

template<typename T>                       //����ʼ��λ��p��n��Ԫ����ѡ�������
ListNode<T> *List<T>::selectMax(ListNode<T> *p, int n) {
    ListNodePosi(T) max = p;               //������ݶ�Ϊ���p
    for (ListNodePosi(T) cur = p; n > 1; n--) {                   //���׽ڵ�p����,�������ڵ���һ��max�Ƚ�
        cur = cur->succ;
        if (cur->data > max->data) {
            max = cur;
        }
    }                                      //�������Ԫ��λ�ü�¼
    return max;                            //�������ڵ�λ��
}

template<typename T>                       //�����б�Ĺ鲢:��ǰ�б�����p���n��Ԫ��,���б�L����q���m��Ԫ�ع鲢
void List<T>::merge(ListNode<T> *&p, int n, List<T> &L, ListNode<T> *q, int m) {
    ///ע��:�ڹ鲢����֮��ĳ���,�п��� this == L && rank(p) + n = rank(q)
    ListNodePosi(T) pp = p->pred;          //����ǰ��(�п�����header),�Ա㷵��ǰ...
    while (m > 0) {                        //��q��δ�Ƴ�����ǰ
        if ( n > 0 && p->data <= q->data) {                      //��p���������ڲ���v(p) <= v(q), ��
            p = p->succ;
            if (q == p) {                  //p����ϲ����б�,���滻Ϊ��ֱ�Ӻ��
                n--;
                break;
            } else {                       //��p�Ѿ������ҽ����v(q) < v(p),��
                q = q->succ;
                insertB(p, L.remove(q->pred));             //��qת����p֮ǰ
                m--;
            }
        }
    }
    p = pp->succ;                          //ȷ���鲢������ĵ����
}

template<typename T>                       //�б�Ĺ鲢�����㷨:����ʼλ��Ϊp��n��Ԫ������
void List<T>::mergeSort(ListNode<T> *&p, int n) {                   //valid(p) && rank(p) + n <= size
    if (n < 2) {                           //�����򷵻��Ѿ��㹻С,��ֱ�ӷ���,����...
        return ;
    }
    int m = n >> 1;                        //���е�Ϊ��
    ListNodePosi(T) q = p;
    for (int i = 0; i < m; i++) {          //�����б�
        q = q->succ;
    }
    mergeSort(p, m);                 //��ǰ�����б�ֱ�����
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);          //�鲢
}                                          //ע��:�����,p��Ȼָ��鲢�������(��)���

template<typename T>                       //����[]�����,ʹ���ܹ����±�����б�
T &List<T>::operator[](int r) const {
    ListNodePosi(T) p = header->pred;
    for (int i = 0; i < r; i++) {
        p = p->succ;
    }
    return p->data;
}

template<typename T>                       //��ת�����б�
void List<T>::reverse() {
    ListNodePosi(T) p = header->succ;
    ListNodePosi(T) q = trailer->pred;
    while (p != q || p->succ == q) {                       //������ַ
        ListNodePosi(T) tempP = p->pred;         //����p�ĵ�ǰ��ַ,����ı�q��ֵ
        p->pred->succ = q;
        p->succ->pred = q;
        p->pred = q->pred;
        p->succ = q->succ;
        q->pred->succ = p;
        q->succ->pred = p;
        q->pred = tempP;
        q->succ = tempP->succ->succ;
        ListNodePosi(T) swapTemp = q;      //ʹp,q���¹�λ���ҵ���
        q = p;
        p = swapTemp;
        p = p->succ;
        q = q->pred;
    }
}

template<typename T>                       //�ж��б��Ƿ��Ѿ�����,��������ԵĶ���
int List<T>::disordered() const {
    int count = 0;
    ListNodePosi(T) p = header->succ;
    ListNodePosi(T) q = p->succ;
    while (q != trailer) {
        if (q->data > p->data) {
            count++;
        }
        q = q->succ;
        p = p->succ;
    }
    return count;
}

//
// Created by wjy on 22-6-17.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H
#define ListNodePosi(T) ListNode<T>*

template <typename T> struct ListNode {
//��Ա
    T data;                    //��ֵ
    ListNodePosi(T) pred;      //ǰ��
    ListNodePosi(T) succ;      //����
//���캯��
    ListNode() = default;
    explicit ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), pred(p), succ(s) {}
//�����ӿ�
    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};

template<typename T>class List{
private:
    int _size;                        //��ģ
    ListNodePosi(T) header;           //ͷ�ڱ�
    ListNodePosi(T) trailer;          //β�ڱ�
protected:
    void init();              //�����б�ʱ�ĳ�ʼ��
    int clear();              //������нڵ�
    void copyNodes(ListNodePosi(T), int);          //�����б�����λ��p���n��
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);             //�鲢
    void mergeSort(ListNodePosi(T)&, int);         //�Դ�p��ʼ������n���ڵ�鲢����
    void selectSort(ListNodePosi(T), int);        //�Դ�p��ʼ������n���ڵ�ѡ������
    void insertionSort(ListNodePosi(T), int);     //�Դ�p��ʼ������n���ڵ��������
public:
//���캯��
    List() {init();}       //Ĭ��
    List(List<T> const& L);            //���帴���б�L
    List(List<T> const& L, int r, int n);            //�����б�����r���n��
    List(ListNodePosi(T) p, int n);                  //�����б�����λ��p���n��
//��������
    ~List();
//ֻ�����ʽӿ�
    int size() const {return _size;}       //��ģ
    bool empty() const {return _size <= 0;}        //�п�
    T& operator[] (int r) const;           //����֧��ѭ�ȷ���(��Ч��)
    ListNodePosi(T) first() const {return header->succ;}    //�׽ڵ�λ��
    ListNodePosi(T) last() const {return trailer->pred;}    //β�ڵ�λ��
    bool valid(ListNodePosi(T) p) {                 //�ж�λ��p�Ƿ�Ϸ�
        return p && (trailer != p) && (header != p);
    }
    int disordered() const;            //�ж��б��Ƿ�������
    ListNodePosi(T) find(T const& e) const {        //�����б����
        return find (e, _size, trailer);
    }
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;   //�����������
    ListNodePosi(T) search(T const& e) {                   //�����б����
        return search(e, _size, trailer);
    }
    ListNodePosi(T) search(T const& a, int n, ListNodePosi(T) p) const;   //�����������
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);         //��p�Լ��Ժ�n-1�������ѡ������
    ListNodePosi(T) selectMax() {                                //�������ֵ
        selectMax(header->succ, _size);
    }
//�ɷ��ʽӿ�
    ListNodePosi(T) insertAsFirst(T const& e);      //��e�����׽ڵ����
    ListNodePosi(T) insertAsLast(T const& e);       //��e����β�ڵ����
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);      //��e��Ϊp�ĺ�̲���
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);      //��e��Ϊp��ǰ������
    T remove(ListNodePosi(T) p);                    //ɾ���Ϸ�λ��p���Ľڵ�, ���ر�ɾ���Ľڵ�
    void merge(List<T>& L) {                        //ȫ�б�鲢
        merge(first(), _size, L, L.first(), L._size);
    }
    void sort(ListNodePosi(T) p, int n);             //�б���������
    void sort() {                                    //�б���������
        sort(first(), _size);
    }
    int deduplicate();             //����ȥ��
    int uniquifiy();               //����ȥ��
    void reverse();                //ǰ����(�Լ�ʵ��)
//����
    void traverse(void (*) (T &));            //����,����ʵʩvisit����(����ָ��,ֻ�����߾ֲ����޸�)
    template<typename VST>         //������
    void traverse(VST&);                      //����,����ʵʩvisit����(����ָ��,��ȫ�����޸�)
};           //List
#endif //LIST_LIST_H

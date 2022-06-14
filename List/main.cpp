#include <iostream>

#define ListNodePosi(T) ListNode<T>*

template <typename T> struct ListNode {
//成员
    T data;                    //数值
    ListNodePosi(T) pred;      //前驱
    ListNodePosi(T) succ;      //后驱
//构造函数
    ListNode() = default;
    explicit ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), pred(p), succ(s) {}
//操作接口
    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};

template<typename T>class List{
private:
    int _size;                        //规模
    ListNodePosi(T) header;           //头哨兵
    ListNodePosi(T) trailer;          //尾哨兵
protected:
    void init();              //创建列表时的初始化
    int clear();              //清除所有节点
    void copyNodes(ListNodePosi(T), int);          //复制列表中自位置p起的n项
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);             //归并
    void mergeSort(ListNodePosi(T)&, int);         //对从p开始连续的n个节点归并排序
    void selectSort(ListNodePosi(T), int);        //对从p开始连续的n个节点选择排序
    void insertionSort(ListNodePosi(T), int);     //对从p开始连续的n个节点插入排序
public:
//构造函数
    List() {init();}       //默认
    List(List<T> const& L);            //整体复制列表L
    List(List<T> const& L, int r, int n);            //复制列表中自r起的n项
    List(ListNodePosi(T) p, int n);                  //复制列表中自位置p起的n项
//析构函数
    ~List();
//只读访问接口
    int size() const {return _size;}       //规模
    bool empty() const {return _size <= 0;}        //判空
    T& operator[] (int r) const;           //重载支持循秩访问(低效率)
    ListNodePosi(T) first() const {return header->succ;}    //首节点位置
    ListNodePosi(T) last() const {return trailer->pred;}    //尾节点位置
    bool valid(ListNodePosi(T) p) {                 //判断位置p是否合法
        return p && (trailer != p) && (header != p);
    }
    int disordered() const;            //判断列表是否已排序
    ListNodePosi(T) find(T const& e) const {        //无序列表查找
        return find (e, _size, trailer);
    }
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;   //无序区间查找
    ListNodePosi(T) search(T const& e) {                   //有序列表查找
        return search(e, _size, trailer);
    }
    ListNodePosi(T) search(T const& a, int n, ListNodePosi(T) p) const;   //有序区间查找
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);         //在p以及以后n-1个后继中选出最大的
    ListNodePosi(T) selectMax() {                                //整体最大值
        selectMax(header->succ, _size);
    }
//可访问接口
    ListNodePosi(T) insertAsFirst(T const& e);      //将e当作首节点插入
    ListNodePosi(T) insertAsLast(T const& e);       //将e当作尾节点插入
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);      //将e作为p的后继插入
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);      //将e作为p的前驱插入
    T remove(ListNodePosi(T) p);                    //删除合法位置p处的节点, 返回被删除的节点
    void merge(List<T>& L) {                        //全列表归并
        merge(first(), _size, L, L.first(), L._size);
    }
    void sort(ListNodePosi(T) p, int n);             //列表区间排序
    void sort() {                                    //列表整体排序
        sort(first(), _size);
    }
    int deduplicate();             //无序去重
    int uniquifiy();               //有序去重
    void reverse();                //前后倒置(自己实现)
//遍历
    void traverse(void (*) (T &));            //遍历,依次实施visit操作(函数指针,只读或者局部性修改)
    template<typename VST>         //操作器
    void traverse(VST&);                      //遍历,依次实施visit操作(函数指针,可全局性修改)
};           //List

template<typename T>
void List<T>::init() {     //列表初始化
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;                //记录大小
}

template<typename T>    //在无序列表内节点p的n个前驱中,找到等于e的最后者
ListNodePosi(T) List<T>::find(const T &e, int n, ListNodePosi(T) p) const {
    while (n-- > 0) {                  //从右向左
        if (e == p->pred->data) {
            return p->pred;
        }
        p = p->pred;
    }
    return nullptr;            //失败时返回空指针
}

template<typename T>           //将e作为首节点插入
ListNodePosi(T) List<T>::insertAsFirst(const T &e) {
    _size++;
    return header->insertAsSucc(e);
}

template<typename T>           //将e作为末节点插入
ListNodePosi(T) List<T>::insertAsLast(const T &e) {
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>            //将e作为p的后继插入
ListNode<T> *List<T>::insertA(ListNode<T> *p, const T &e) {
    _size++;
    return p->insertAsSucc(e);
}

template<typename T>            //将e作为p的前驱插入
ListNode<T> *List<T>::insertB(ListNode<T> *p, const T &e) {
    _size++;
    return p->insertAsPred(e);
}

template<typename T>
ListNode<T> *ListNode<T>::insertAsPred(T const &e) {
    ListNodePosi(T) x = new ListNode<T> (e, pred, this);      //创建新节点
    pred->succ = x;                                           //设置正向链接
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

template<typename T>         //列表内部方法:复制列表中自位置p起的n项
void List<T>::copyNodes(ListNode<T> *p, int n) {          //p合法,且有至少n-1个真后继节点
    init();                  //创建头,尾哨兵节点并且初始化
    while (n--) {
        insertAsLast(p->data);
        p = p->succ;            //将自p起的n项依次作为末节点插入
    }
}

template<typename T>         //复制列表中自位置p起的n项
List<T>::List(ListNode<T> *p, int n) {
    copyNodes(p, n);
}

template<typename T>          //整体复制列表L
List<T>::List(const List<T> &L) {
    copyNodes(L.first(), L._size);
}

template<typename T>         //复制L中自第r项起的n项
List<T>::List(const List<T> &L, int r, int n) {
    copyNodes(L[r], n);
}

template<typename T>         //删除合法节点p,返回其数值
T List<T>::remove(ListNode<T> *p) {
    T e = p->data;
    p->pred->succ = p->succ;        //交换前驱后继
    p->succ->pred = p->pred;
    delete p;                       //释放节点,更新大小
    _size--;
    return e;
}

template<typename T>
List<T>::~List() {           //列表析构器
    clear();                 //清空列表,释放头尾哨兵节点
    delete header;
    delete trailer;
}

template<typename T>        //清空列表
int List<T>::clear() {
    int oldsize = _size;
    while(_size > 0) {
        remove(header->succ);        //反复删除节点,直到变为空
    }
    return oldsize;
}

template<typename T>         //剔除无序列表中的重复节点
int List<T>::deduplicate() {
    if (_size < 2) {         //平凡列表无重复
        return 0;
    }
    int oldSize = _size;
    ListNodePosi(T) p = header;           //p从首节点开始
    int r = 0;
    while (trailer != (p = p->succ)) {        //依次直到末节点
        ListNodePosi(T) q = find (p->data, r , p);         //在p的r个前驱中查找重复
        q ? remove(q) : r++;               //若的确存在则删除,否则秩加一
    }
    return oldSize - _size;                   //返回列表大小变化量
}

template<typename T>                      //借助函数指针机制遍历
void List<T>::traverse(void (*visit) (T &)) {
    for (ListNodePosi(T) p = header; p != trailer; p = p->succ) {
        visit (p->data);
    }
}

template<typename T>
template<typename VST>            //元素类型,操作器
void List<T>::traverse(VST &visit) {
    for (ListNodePosi(T) p = header; p != trailer; p = p->succ) {
        visit(p->data);
    }
}

template<typename T>             //剔除有序列表的重复点
int List<T>::uniquifiy() {        //成批删除重复元素,效率更高
    if (_size < 2) {
        return 0;
    }
    int oldSize = _size;
    ListNodePosi(T) p = first();
    ListNodePosi(T) q;
    while (trailer != (q = p->succ)) {
        if (p->data != q->data) {          //若互异,则转向下一区段
            p = q;
        } else {
            remove(q);                  //否则删除后者
        }
    }
    return oldSize - _size;                //返回列表变化大小
}

template<typename T>                      //在有序列表内节点p的n个前驱中找到不大于e的最后者
ListNode<T> *List<T>::search(const T &e, int n, ListNode<T> *p) const {
    while (n-- >= 0) {                    //对于p的最近的b个前驱,从右向左逐个比较
        p = p->pred;
        if (p->data <= e) {               //直到命中或者数值越界或者范围越界
            break;
        }
    }
    return p;                             //返回查找终止的位置
}                                  //失败时,返回区间的左边界(有可能是header)可以使用valid函数判断成功与否

template<typename T>                      //排序的统一入口
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


template<typename T>                      //列表的插入排序:对起始位置为p的n个元素排序
void List<T>::insertionSort(ListNode<T> * p, int n) {
    for (int i = 0; i < n; i++) {         //逐一为各个节点
        insertA(search(p->data, i, p), p->data);
        p = p->succ;                      //转向下一节点
        remove(p->pred);
    }
}

template<typename T>                       //列表的选择排序法:对起始于位置p的n个元素排序
void List<T>::selectSort(ListNode<T> *p, int n ) {
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; i++) {          //待排序区间为(head, tail)
        tail = tail->succ;
    }
    while (1 < n) {                        //在至少还剩两个节点之前,在待排序区间内
        ListNodePosi(T) max = selectMax(head->succ, n);           //找出最大者(歧义时后者优先)
        insertB(tail, remove(max));                     //将其转移到无序区间的末尾(作为有序区间新的收首元素)
        tail = tail->pred;
        n--;
    }
}

template<typename T>                       //从起始于位置p的n个元素中选出最大者
ListNode<T> *List<T>::selectMax(ListNode<T> *p, int n) {
    ListNodePosi(T) max = p;               //最大者暂定为起点p
    for (ListNodePosi(T) cur = p; n > 1; n--) {                   //从首节点p出发,将后续节点逐一与max比较
        cur = cur->succ;
        if (cur->data > max->data) {
            max = cur;
        }
    }                                      //更新最大元素位置记录
    return max;                            //返回最大节点位置
}

template<typename T>                       //有序列表的归并:当前列表中自p起的n个元素,与列表L中自q起的m个元素归并
void List<T>::merge(ListNode<T> *&p, int n, List<T> &L, ListNode<T> *q, int m) {
    ///注意:在归并排序之类的场合,有可能 this == L && rank(p) + n = rank(q)
    ListNodePosi(T) pp = p->pred;          //借助前驱(有可能是header),以便返回前...
    while (m > 0) {                        //在q尚未移出区间前
        if ( n > 0 && p->data <= q->data) {                      //若p仍在区间内并且v(p) <= v(q), 则
            p = p->succ;
            if (q == p) {                  //p归入合并的列表,并替换为其直接后继
                n--;
                break;
            } else {                       //若p已经超出右界或者v(q) < v(p),则
                q = q->succ;
                insertB(p, L.remove(q->pred));             //将q转移至p之前
                m--;
            }
        }
    }
    p = pp->succ;                          //确定归并后区间的的起点
}

template<typename T>                       //列表的归并排序算法:对起始位置为p的n个元素排序
void List<T>::mergeSort(ListNode<T> *&p, int n) {                   //valid(p) && rank(p) + n <= size
    if (n < 2) {                           //若排序返回已经足够小,则直接返回,否则...
        return ;
    }
    int m = n >> 1;                        //以中点为界
    ListNodePosi(T) q = p;
    for (int i = 0; i < m; i++) {          //均分列表
        q = q->succ;
    }
    mergeSort(p, m);                 //对前后子列表分别排序
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);          //归并
}                                          //注意:排序后,p依然指向归并后区间的(新)起点

template<typename T>                       //重载[]运算符,使其能够用下标访问列表
T &List<T>::operator[](int r) const {
    ListNodePosi(T) p = header->pred;
    for (int i = 0; i < r; i++) {
        p = p->succ;
    }
    return p->data;
}

template<typename T>                       //翻转整个列表
void List<T>::reverse() {
    ListNodePosi(T) p = header->succ;
    ListNodePosi(T) q = trailer->pred;
    while (p != q || p->succ == q) {                       //交换地址
        ListNodePosi(T) tempP = p->pred;         //储存p的当前地址,方便改变q的值
        p->pred->succ = q;
        p->succ->pred = q;
        p->pred = q->pred;
        p->succ = q->succ;
        q->pred->succ = p;
        q->succ->pred = p;
        q->pred = tempP;
        q->succ = tempP->succ->succ;
        ListNodePosi(T) swapTemp = q;      //使p,q重新归位并且迭代
        q = p;
        p = swapTemp;
        p = p->succ;
        q = q->pred;
    }
}

template<typename T>                       //判断列表是否已经有序,返回无序对的对数
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



int main() {

    return 0;
}

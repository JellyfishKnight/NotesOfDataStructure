//
// Created by wjy on 22-6-17.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H
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
#endif //LIST_LIST_H

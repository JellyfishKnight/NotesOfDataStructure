//
// Created by wjy on 22-6-14.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#define DEFAULT_CAPACITY 20     //默认的初始容量(实际应用中可设置为更大)

typedef int Rank;

template<typename T>  //向量模板类
class Vector{
protected:
    Rank _size;        //规模
    int _capacity;     //容量
    T* _elem;          //数据区
    void copyFrom(T const* A, Rank lo, Rank hi);     //复制数组区间A[lo, hi]
    void expand();                                   //空间不足时扩容
    void shrink();                                   //装填因子过小时压缩
    bool bubble(Rank lo, Rank hi);                   //扫描交换
    void bubbleSort(Rank lo, Rank hi);               //冒泡排序
    Rank max(Rank lo, Rank mi, Rank hi);             //选取最大元素
    void selectionSort(Rank lo, Rank hi);            //选择排序
    void merge(Rank lo, Rank mi, Rank hi);                                    //归并算法
    void mergeSort(Rank lo, Rank hi);                                //归并排序算法
    Rank partition(Rank lo, Rank hi);                //轴点构造法
    //快速排序算法
    void heapSort(Rank lo, Rank hi);                 //堆排序算法
public:
    //构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { //容量为c,规模为s,所有元素初始为v
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }
    Vector(T const* A, Rank n) {                     //数组整体复制
        copyFrom(A, 0, n);
    }
    Vector(T const* A, Rank lo, Rank hi) {           //区间复制
        copyFrom(A, lo, hi);
    }
    Vector(Vector<T> const& v) {                     //向量整体复制
        copyFrom(v._elem, 0, v._size);
    }
    Vector(Vector<T> const& v, Rank lo, Rank hi) {   //区间复制
        copyFrom(v._elem, lo, hi);
    }
    ~Vector() {                                      //析构函数
        delete [] _elem;
    }
    Rank size() const {                              //规模
        return _size;
    }
    bool empty() const {                             //判空
        return !_size;
    }
    int disordered() const;                          //判断向量是否已经排序
    Rank find(T const& e) {                          //无序向量整体查找
        return find(e, 0, _size);
    }
    Rank find(T const& e, Rank lo, Rank hi) const;   //无序向量区间查找
    Rank search(T const& e) const {                  //有序向量整体查找
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找
    //只写访问接口
    const T& operator[] (Rank r) const;                    //重载下表运算符,可以类似与数组形式引用各元素
    Vector<T>& operator= (Vector<T> const&);         //重载赋值运算符,以便克隆向量
    T remove(Rank r);                                //删除秩为r的元素
    int remove(Rank lo, Rank hi);                    //删除区间[lo,hi]的元素并返回删除元素的个数
    Rank insert(Rank r, T const& e);                 //插入元素
    Rank insert(T const& e) {                        //默认作为末元素插入
        return insert(_size, e);
    }
    void sort(Rank lo, Rank hi);                     //给区间[lo,hi]排序
    void sort() {                                    //向量整体排序
        sort(0, _size);
    }
    void unsort(Rank lo, Rank hi);                   //对[lo,hi]区间置乱
    void unsort() {                                  //向量整体置乱
        unsort(0, _size);
    }
    int deduplicate();                               //无序去重
    int uniquify();                                  //有序去重
    //遍历
    void traverse(void(*) (T&));                     //遍历(使用函数指针,只读或局部性修改)
    template<typename VST>                           //遍历(使用函数对象,全局性修改)
    void traverse(VST&);

    void quickSort(Rank lo, Rank hi);
};

#endif //VECTOR_VECTOR_H

//
// Created by wjy on 22-6-14.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#define DEFAULT_CAPACITY 20     //Ĭ�ϵĳ�ʼ����(ʵ��Ӧ���п�����Ϊ����)

typedef int Rank;

template<typename T>  //����ģ����
class Vector{
protected:
    Rank _size;        //��ģ
    int _capacity;     //����
    T* _elem;          //������
    void copyFrom(T const* A, Rank lo, Rank hi);     //������������A[lo, hi]
    void expand();                                   //�ռ䲻��ʱ����
    void shrink();                                   //װ�����ӹ�Сʱѹ��
    bool bubble(Rank lo, Rank hi);                   //ɨ�轻��
    void bubbleSort(Rank lo, Rank hi);               //ð������
    Rank max(Rank lo, Rank mi, Rank hi);             //ѡȡ���Ԫ��
    void selectionSort(Rank lo, Rank hi);            //ѡ������
    void merge(Rank lo, Rank mi, Rank hi);                                    //�鲢�㷨
    void mergeSort(Rank lo, Rank hi);                                //�鲢�����㷨
    Rank partition(Rank lo, Rank hi);                //��㹹�취
    //���������㷨
    void heapSort(Rank lo, Rank hi);                 //�������㷨
public:
    //���캯��
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { //����Ϊc,��ģΪs,����Ԫ�س�ʼΪv
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }
    Vector(T const* A, Rank n) {                     //�������帴��
        copyFrom(A, 0, n);
    }
    Vector(T const* A, Rank lo, Rank hi) {           //���临��
        copyFrom(A, lo, hi);
    }
    Vector(Vector<T> const& v) {                     //�������帴��
        copyFrom(v._elem, 0, v._size);
    }
    Vector(Vector<T> const& v, Rank lo, Rank hi) {   //���临��
        copyFrom(v._elem, lo, hi);
    }
    ~Vector() {                                      //��������
        delete [] _elem;
    }
    Rank size() const {                              //��ģ
        return _size;
    }
    bool empty() const {                             //�п�
        return !_size;
    }
    int disordered() const;                          //�ж������Ƿ��Ѿ�����
    Rank find(T const& e) {                          //���������������
        return find(e, 0, _size);
    }
    Rank find(T const& e, Rank lo, Rank hi) const;   //���������������
    Rank search(T const& e) const {                  //���������������
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const; //���������������
    //ֻд���ʽӿ�
    const T& operator[] (Rank r) const;                    //�����±������,����������������ʽ���ø�Ԫ��
    Vector<T>& operator= (Vector<T> const&);         //���ظ�ֵ�����,�Ա��¡����
    T remove(Rank r);                                //ɾ����Ϊr��Ԫ��
    int remove(Rank lo, Rank hi);                    //ɾ������[lo,hi]��Ԫ�ز�����ɾ��Ԫ�صĸ���
    Rank insert(Rank r, T const& e);                 //����Ԫ��
    Rank insert(T const& e) {                        //Ĭ����ΪĩԪ�ز���
        return insert(_size, e);
    }
    void sort(Rank lo, Rank hi);                     //������[lo,hi]����
    void sort() {                                    //������������
        sort(0, _size);
    }
    void unsort(Rank lo, Rank hi);                   //��[lo,hi]��������
    void unsort() {                                  //������������
        unsort(0, _size);
    }
    int deduplicate();                               //����ȥ��
    int uniquify();                                  //����ȥ��
    //����
    void traverse(void(*) (T&));                     //����(ʹ�ú���ָ��,ֻ����ֲ����޸�)
    template<typename VST>                           //����(ʹ�ú�������,ȫ�����޸�)
    void traverse(VST&);

    void quickSort(Rank lo, Rank hi);
};

#endif //VECTOR_VECTOR_H

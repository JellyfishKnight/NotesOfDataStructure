//
// Created by wjy on 22-6-14.
//

#include "iostream"
#include "Vector.h"


template<typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &V) {
    if (_elem) {
        delete [] _elem;
    }
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template<typename T>
T &Vector<T>::operator[](Rank r) const {
    if (_elem && r < _size) {
        return _elem[r];
    }
    return -1;
}

template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) {
        return ;
    }
    if (_capacity < DEFAULT_CAPACITY) {
        _capacity = DEFAULT_CAPACITY;
    }
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++) {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) {
        return;
    }
    if (_size << 2 > _capacity) {
        return;
    }
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++) {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

template<typename T>
void permute(Vector<T>& v) {
    for (int i = v.size(); i > 0; i--) {
        Rank t = rand() % i;
        T temp = v[i - 1];
        v[i - 1] = v[t];
        v[t] = temp;
    }
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    T* v = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--) {
        Rank t = rand() % i;
        T temp = v[i - 1];
        v[i - 1] = v[t];
        v[t] = temp;
    }
}

template<typename T>
static bool lt (T* a, T* b) {
    return lt(*a, *b);
}

template<typename T>
static bool lt(T& a, T&b) {
    return a < b;
}

template<typename T>
static bool eq(T* a, T* b) {
    return eq(*a, *b);
}

template<typename T>
static bool eq(T& a, T& b) {
    return a == b;
}

template<typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T &e) {
    expand();
    for (int i = _size; i > r; i--) {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    _size++;
    return r;
}

template<typename T>
T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) {
        return 0;
    }
    while (hi < _size) {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();
    return hi - lo;
}

template<typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 1;
    while (i < _size) {
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    }
    return oldSize - _size;
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

template<typename T> template<typename VST>
void Vector<T>::traverse(VST &visit) {
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

template<typename T>
struct Increase {
            virtual void operator() (T& e) {
                e++;
            }
        };

template<typename T>
void increase(Vector<T>& v) {
    v.template traverse(Increase<T>());
}

template<typename T>
int Vector<T>::disordered() const {
    int n = 0;
    for (int i = 1; i < _size; i++) {
        if (_elem[i - 1] > _elem[i]) {
            n++;
        }
    }
    return n;
}


template<typename T>
int Vector<T>::uniquify() {
    Rank i = 0;
    Rank j = 0;
    while (++j < _size) {
        if (_elem[i] != _elem[j]) {
            _elem[++i] = _elem[j];
        }
    }
    _size = ++i;
    shrink();
    return j - i;
}

template<typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    return binSearch(_elem, e, lo, hi);
}

template<typename T>
static Rank binSearch(T* a, T const& e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        (e < a[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    switch (rand() % 3) {
        case 1:
            bubbleSort(lo, hi);
            break;
        case 2:
            selectionSort(lo, hi);
            break;
        case 3:
            mergeSort(lo, hi);
            break;
        default:
            mergeSort(lo, hi);
            break;
    }
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (!bubble(lo, hi--));
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool sorted = true;
    while (++lo < hi) {
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            T temp = _elem[lo - 1];
            _elem[lo - 1] = _elem[lo];
            _elem[lo] = temp;
        }
    }
    return sorted;
}

template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
    for (int i = lo; i < hi; i++) {
        for (int j = i + 1; j < hi; j++) {
            if (_elem[i] > _elem[j]) {
                T temp = _elem[lo - 1];
                _elem[lo - 1] = _elem[lo];
                _elem[lo] = temp;
            }
        }
    }
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2) {
        return ;
    }
    int mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi ,hi);
    merge(lo, mi, hi);
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* a = _elem + lo;
    int lb = mi - lo;
    T* b = new T[lb];
    for (Rank i = 0; i < lb; b[i] = a[i++]);
    int lc = hi - mi;
    T* c = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
        if ((j < lb) && (!(k < lc) || (b[j] < c[k]))) {
            a[i++] = b[j++];
        }
        if ((k < lc) && (!(j < lb) || (c[k] < b[j]))) {
            a[i++] = c[k++];
        }
    }
    delete [] b;
}




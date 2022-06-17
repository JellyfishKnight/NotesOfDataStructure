//
// Created by wjy on 22-6-14.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H
#include "../Vector/Vector.h"

template<typename T>
class Stack : public Vector<T> {
public:
    void push(T const& e) {
        this->insert(this->size(), e);
    }
    T pop() {
        return remove(this->size() - 1);
    }
    T& top() {
        return (*this) [this->size() - 1];
    }
};

void convert_reverse(Stack<char>& s, int n, int base);

void convert_range(Stack<char>& s, int n, int base);

#endif //STACK_STACK_H

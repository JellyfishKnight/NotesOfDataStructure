//
// Created by wjy on 22-6-14.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H
#include <iostream>
#include "List.h"

template<typename T>
class Queue : public List<T> {
public:
    void enqueue(T const& e) {        //入队,尾部插入
        this->insertAsLast(e);
    }
    T dequeue() {                     //出队,首部删除
        return this->remove(this->first());
    }
    T& front() {                      //队首
        return this->first()->data;
    }
};
#endif //QUEUE_QUEUE_H

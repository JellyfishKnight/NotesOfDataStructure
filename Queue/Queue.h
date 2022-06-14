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
    void enqueue(T const& e) {        //���,β������
        this->insertAsLast(e);
    }
    T dequeue() {                     //����,�ײ�ɾ��
        return this->remove(this->first());
    }
    T& front() {                      //����
        return this->first()->data;
    }
};
#endif //QUEUE_QUEUE_H

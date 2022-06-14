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
/**
 * @brief 银行服务模拟
 */
struct Customer{                //顾客类
    int window;                 //所属窗口(队列)
    unsigned int time;          //服务时长
};

int bestWindow(Queue<Customer> windows[], int nWin) {         //为新顾客确定最佳队列
    int minSize = windows[0].size();                          //最优队列(窗口)
    int optiWin = 0;
    for (int i = 1; i < nWin; i++) {                          //在所有窗口中
        if (minSize > windows[i].size()) {                    //挑选出队列最短者
            minSize = windows[i].size();
            optiWin = i;
        }
    }
    return  optiWin;                                          //返回
}


void simulate(int nWin, int serverTime) {         //按指定窗口数,服务总时间模拟银行业务
    auto* windows = new Queue<Customer>[nWin];        //为每一个窗口创造一个队列
    for (int now = 0; now < serverTime; now++) {                 //在下班之前,每个一个单位的时间
        Customer c{};                                              //新顾客到达,服务时长随机确定
        c.time = 1 + rand() % 98;
        c.window = bestWindow(windows, nWin);                    //为新顾客找出最佳服务窗口
        windows[c.window].enqueue(c);                         //新顾客加入最佳队列
    }
    for (int i = 0; i < nWin; i++) {                    //分别检查
        if (!windows[i].empty()) {                      //各个非空队列
            if (--windows[i].front().time <= 0) {       //队首顾客服务时常减少一个单位
                windows[i].dequeue();                   //服务完毕的顾客出列,由后继顾客接替
            }
        }
    }
    delete [] windows;              //释放所有的队列(此前,~List()会自动清空队列)
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

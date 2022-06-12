#include <iostream>
#include "stack"
#include "algorithm"


using namespace std;



struct queen{         //皇后类
    int x, y;         //皇后在棋盘上的位置坐标
    explicit queen(int xx = 0, int yy = 0) : x(xx), y(yy) {}
    bool operator==(queen const& q) const {          //重载判等运算符,以检测不同皇后之间可能的冲突
        return (x == q.x) ||                         //行冲突(可省略)
                (y == q.y) ||                        //列冲突
                (x + y == q.x + q.y) ||              //沿正对角线冲突
                (x - y == q.x - q.y);                //沿反对角线冲突
    }
    bool operator!=(queen const& q) const {          //重载不等运算符
        return !(*this == q);
    }
};


template<typename T>
int find(T t, stack<T> s) {
    for (int i = s.size() - 1; !s.empty(); i--) {
        if (t.x - s.top().x == t.y - s.top().y) {
            return --i;
        } else {
            s.pop();
        }
    }
    return -1;
}


void placeQueens(int n, stack<queen>& solu) {           //N皇后算法(迭代版):采用试探/回溯的策略,借助栈记录查找的结果
    //solu:存放(部分)解的栈
    queen q(0, 0);
    while (q.y < n) {
        if () {

        } else {
            while (q.y < n && find(q, solu) >= 0) {
                q.y++;
            }
            if (n > q.y && find(q, solu) == -1) {
                solu.push(q);
                q.y++;
            } else {
                q.x++;
            }
        }
    }
}



int main() {
    stack<queen> solu;
    placeQueens(8, solu);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == solu.top().x && j == solu.top().y) {
                cout << "1" << " ";
                solu.pop();
            } else {
                cout << "0" << " ";
            }
        }
        cout << endl;
    }
    return 0;
}

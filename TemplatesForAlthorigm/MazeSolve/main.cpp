#include <iostream>
#include "stack"

using namespace std;

typedef enum {AVAILABLE, ROUTE, BACKTRACKED, WALL} Status;      //迷宫单元状态
//原始可用的,在当前路径上的,所有方向均尝试失败回溯过的,不可使用的(墙)
typedef enum {UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY} ESWN;
//未定,东,南,西,北,无路可通
inline ESWN nextESWN (ESWN eswn) {          //依次转至下一邻格方向
    return ESWN (eswn + 1);
}

struct Cell{                     //迷宫格点
    int x;                       //x坐标,y坐标,类型
    int y;
    Status status;
    ESWN incoming, outgoing;     //进入.走出方向
};

#define LABY_MAX 24              //最大迷宫尺寸
Cell laby[LABY_MAX][LABY_MAX];   //迷宫

inline Cell* neighbor (Cell* cell) {         //查询当前位置的相邻格点
    switch (cell->outgoing) {
        case EAST:                           //向东
            return cell + LABY_MAX;
        case SOUTH:                          //向南
            return cell + 1;
        case WEST:                           //向西
            return cell - LABY_MAX;
        case NORTH:                          //向北
            return cell - 1;
        default:
            exit(1);
    }
}

inline Cell* advance (Cell* cell) {          //从当前位置转入相邻格点
    Cell* next;
    switch (cell->outgoing) {
        case EAST:                           //向东
            next = cell + LABY_MAX;
            next->incoming = WEST;
            break;
        case SOUTH:                          //向南
            next = cell + 1;
            next->incoming = NORTH;
            break;
        case WEST:                           //向西
            next = cell - LABY_MAX;
            next->incoming = EAST;
            break;
        case NORTH:                          //向北
            next = cell - 1;
            next->incoming = SOUTH;
            break;
        default:
            exit(1);
    }
    return next;
}


//迷宫寻径算法:在单元格s到t之间规划一条通路(如果确实存在)
bool labyrinth (Cell Laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t) {
    if (AVAILABLE != s->status || AVAILABLE != t->status) {                 //退化情况
        return false;
    }
    stack<Cell*> path;                         //用栈来记录通路
    s->incoming = UNKNOWN;
    s->status = ROUTE;
    path.push(s);         //起点
    do {                     //从起点出发不断试探,回溯,直到抵达终点,或者无穷尽可能
        Cell* c = path.top();                  //检查当前位置
        if (c == t) {                          //若已经到了重点,则找到了一条通路u;否则,沿尚未试探方向继续试探
            return true;
        }
        while (NO_WAY > (c->outgoing = nextESWN(c->outgoing))) {       //注意检查所有方向
            if (AVAILABLE == neighbor(c)->status) {                     //试图找到尚未试探方向
                break;
            }
        }
        if (NO_WAY <= c->outgoing) {                                        //如果所有的方向都已经尝试过
            c->status = BACKTRACKED;                                        //向后回溯一步
            c = path.top();
            path.pop();
        } else {                                                            //否则再试探一步
            path.push(c = advance(c));
            c->outgoing = UNKNOWN;
            c->status = ROUTE;
        }
    } while(!path.empty());
    return false;
}




int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

//
// Created by wjy on 22-6-15.
//

#include "Graph.h"
#include "../Vector/Vector.h"
#include "../Queue/Queue.h"

template<typename Tv, typename Te> //广度优先搜索BFS算法(全图)
void Graph<Tv,Te>::bfs(int s) {    //0 <= s < n
    reset();                       //初始化
    int clock = 0;
    int v = s;
    do {                           //逐一检查所有顶点
        if (UNDISCOVERED == status(v)) { //一旦遇到尚未发现的顶点
            BFS(v, clock);      //即从该顶点出发启动一次BFS
        }
    } while (s != (v = (++v % n)));//按序号检查,故不漏不重
}

template<typename Tv, typename Te> //广度优先搜索BFS算法(单个连通域)
void Graph<Tv, Te>::BFS(int v, int &clock) { //0 <= v < n
    Queue<int> Q;                  //引入辅助队列
    status(v) = DISCOVERED;        //初始化起点
    Q.enqueue(v);
    while (!Q.empty()) {           //在Q变空之前,不断
        int v_temp = Q.dequeue();  //取出队首顶点v_temp
        dTime(v_temp) = ++clock;
        for (int u = firstNbr(v_temp); -1 < u; u = nextNbr(v_temp, u)) { //枚举v的所有邻居
            if (UNDISCOVERED == status(u)) { //若u尚未被发现,则
                status(u) = DISCOVERED;      //发现该顶点
                Q.enqueue(u);
                type(v_temp, u) = TREE;      //引入树边拓展支撑树
                parent(u) = v_temp;
            } else {                         //若u已经被发现,或者甚至已经访问完毕,则
                type(v_temp, u) = CROSS;     //将(v,u)归类于跨边
            }
        }
    }
    status(v) = VISITED;                     //至此,当前顶点访问完毕
}

template<typename Tv, typename Te> //深度优先搜索DFS算法(全图)
void Graph<Tv, Te>::dfs(int s) {   //0 <= s < n
    reset();                       //初始化
    int clock = 0;
    int v = s;
    do {                           //逐一检查所有顶点
        if (UNDISCOVERED == status(v)) { //一旦发现尚未发现的顶点
            DFS(v, clock);      //即从该顶点出发启动一次DFS
        }
    } while (s != (v == (++v % s))); //按序号检查,不重不漏
}

template<typename Tv, typename Te> //深度优先搜索算法DFS(单个连通域)
void Graph<Tv, Te>::DFS(int v, int &clock) { //0 <= v < n
    dTime(v) = ++clock;            //发现当前顶点v
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) { //枚举v的所有邻居
        switch (status(u)) {       //视其状态分别处理
            case UNDISCOVERED:     //u尚未发现,意味着支撑树可在此扩展
                type(v, u) = TREE;
                parent(u) = v;
                DFS(u, clock);
                break;
            case DISCOVERED:       //u已被发现但未访问完毕,应属被后代指向的祖先
                type(v, u) = BACKWARD;
                break;
            default:               //u已访问完毕(VISITED,有向图),则视承袭关系分别为前向边或跨边
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;           //至此,当前顶点v方告访问完毕
    fTime(v) = ++clock;
}
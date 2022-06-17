//
// Created by wjy on 22-6-15.
//

#include "Graph.h"
#include "../Vector/Vector.h"
#include "../Queue/Queue.h"
#include "../Stack/Stack.h"

template<typename T>
T min(T a, T b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

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
    } while (s != (v = (++v % s))); //按序号检查,不重不漏
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

template<typename Tv, typename Te> //基于DFS的拓扑排序算法
Stack<Tv> Graph<Tv, Te>::tSort(int s) { //0 <= s < n
    reset();
    int clock = 0;
    int v = s;
    auto *S = new Stack<Tv>;       //用栈记录排序顶点
    do {
        if (UNDISCOVERED == status(v)) {
            if (!TSort(v, clock, s)) { //clock并非必须
                while (!S->empty()) { //任一连通域(即整图)非DAG
                    S->pop();      //则不必继续计算,故直接返回
                    break;
                }
            }
        }
    } while (s != (v = (++v % n)));
    return S;                      //若输入为DAG,则S内各顶点自顶向底排序,否则(不存在拓扑排序),S空
}

template<typename Tv, typename Te> //基于DFS的拓扑排序算法(单趟)
bool Graph<Tv, Te>::TSort(int v, int &clock, Stack<Tv> *S) { //0 <= v < n
    dTime(v) = ++clock;            //发现顶点v
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {   //枚举v的所有邻居u
        switch (status(u)) {                                 //并视u的状态分别处理
            case UNDISCOVERED:
                parent(u) = v;
                type(v, u) = TREE;
                if (!TSort(u, clock, S)) {             //从顶点u出发深入搜索
                    return false;                            //若u及其后代不能拓扑排序(则亦全图如此), 故返回并作报告
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;                       //一旦发现后向边(非DAG),则
                return false;                                //不必深入,故返回做报告
            default:                                         //VISITED(digraphs only)
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;                                     //顶点被标记为VISITED的时候随即入栈
    S->push(vertex(v));
    return true;                                             //v及其后代可以拓扑排序
}

template<typename Tv, typename Te> //基于DFS的BCC分解算法
void Graph<Tv, Te>::bcc(int s) {
    reset();
    int clock = 0;
    int v = s;
    Stack<int> S;                  //栈S用于记录已访问的顶点
    do {
        if (UNDISCOVERED == status(v)) { //一旦发现未发现的顶点
            BCC(v, clock, s);      //即从该顶点出发启动一次BCC
            S.pop();                     //遍历返回后,弹出栈中最后一个顶点--当前连通域的顶点
        }
    } while (s != (v = ++v % n));
}

#define hca(x) (fTime(x))          //此处利用闲置的fTime[]充当hca[]
template<typename Tv, typename Te> //顶点类型,边类型
void Graph<Tv, Te>::BCC(int v, int &clock, Stack<int> &S) { //0 <= v < n
    hca(v) = dTime(v) = ++clock;                            //v被发现且入栈
    status(v) = DISCOVERED;
    S.push(v);
    for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {  //枚举v所有邻居u
        switch (status(u)) {       //视u情况分别处理
            case UNDISCOVERED:
                parent(u) = v;                              //从顶点u处深入
                type(v, u) = TREE;
                BCC(u, clock, S);
                if (hca(u) < dTime(v)) {                    //遍历返回后,若发现u(通过后向边)可指向v的真祖先
                    hca(v) = min(hca(v), hca(u));     //则v亦如此
                } else {                                    //否则,以v为关节点(u以下即是一个BCC,且其中定点此时正集中于栈S顶部)
                    while (v != S.pop());                   //依次弹出当前BCC中的节点,亦可根据实际需求转存至其他结构
                    S.push(v);                           //最后一个顶点(关节点)重新入栈--分摊不足一次
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;                      //标记(v,u),并按照越小越高的原则
                if (u != parent(v)) {
                    hca(v) = min(hca(v), dTime(u));   //更新hca(v)
                }
                break;
            default:                                        //VISITED (digraphs only)
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;                //对v的访问结束
}

//顶点类型,边类型,优先级更新器
template<typename Tv, typename Te> template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) { //优先级搜索(整个连通域)
    reset();                                     //初始化,s添加到PFS树中
    int v = s;
    do {                        //逐一检查所有顶点
        if (UNDISCOVERED == status(v)) { //一旦发现尚未遇到的顶点
            PFS(v, prioUpdater);      //就从该顶点出发启动一次PFS
        }
    } while (s != (v = (++v % n)));      //按序号检查,不重不漏
}

//顶点类型,边类型,优先级更新器
template<typename Tv, typename Te> template<typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) { //优先级搜索(单个连通域)
    priority(s) = 0;                             //初始化,s添加到PFS树中
    status(s) = VISITED;
    parent(s) = -1;
    while (true) {                               //将下一顶点和边加到PFS树中
        for (int w = firstNbr(s); w > -1; w = nextNbr(s, w)) { //枚举所有邻居w
            prioUpdater(this, s, w);             //更新顶点w的优先级以及其父节点
        }
        for (int shortest = INT_MAX, w = 0; w < n; w++) {
            if (UNDISCOVERED == status(w)) {     //从尚未加入遍历树的顶点中
                if (shortest > priority(w)) {    //选出下一个
                    shortest = priority(w);      //优先级最高的顶点s
                    s = w;
                }
            }
        }
        if (VISITED == status(s)) {              //直到所有顶点都已经加入
            break;
        }
        status(s) = VISITED;                     //将s与其父节点的联边加入遍历树
        type(parent(s), s) = TREE;
    }
}                   //通过定义具体的优先级更新策略prioUpdater,即可实现不同的算法功能

template<typename Tv, typename Te>               //针对Dijkstra算法的顶点优先级更新器
struct DijkstraPU {
            virtual void operator() (Graph<Tv,Te>* g, int uk, int v) { //对于uk每一尚未被发现的邻接顶点v,按Dijkstra策略
                if (UNDISCOVERED == g->status(v)) {
                    if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) { //做松弛
                        g->priority(v) = g->priority(uk) + g->weight(uk, v);   //更新优先级数
                        g->parent(v) = uk; //并同时更新父节点
                    }
                }
            }
        };

//
// Created by wjy on 22-6-15.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include "../Stack/Stack.h"
#include "../Vector/Vector.h"

#define INT_MAX 2e10

typedef enum {                        //顶点状态
    UNDISCOVERED, DISCOVERED, VISITED
} VStatus;

typedef enum {                        //边在遍历树中所属的类型
    UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
} EType;

template<typename Tv, typename Te> //顶点类型
class Graph{                       //图Graph模板类
private:
    void reset() {                 //所有顶点,边的辅助信息复位
        for (int i = 0; i < n; i++) {      //所有顶点的
            status(i) = UNDISCOVERED;      //状态
            dTime(i) = fTime(i) = -1;      //时间标签
            parent(i) = -1;                //(在遍历树中的)父节点
            priority(i) = INT_MAX;         //优先级数
            for (int j = 0; j < n; j++) {  //所有边的
                if (exists(i, j)) {
                    type(i, j) = UNDETERMINED; //类型
                }
            }
        }
    }
    void BFS(int , int&);                  //(连通域)广度优先算法
    void DFS(int , int&);                  //(连通域)深度优先算法
    void BCC(int , int& , Stack<int>&);    //(连通域)基于DFS的双连通分量分解算法
    bool TSort(int , int& , Stack<Tv>*);   //(连通域)基于DFS的拓扑排序算法
    template<typename PU>                  //(连通域)优先级搜索框架
    void PFS(int, PU);
public:
//顶点
    int n{};                                 //顶点总数
    virtual int insert(Tv const&) = 0;     //插入定点,返回编号
    virtual Tv remove(int) = 0;            //删除顶点以及其关联边,返回该顶点信息
    virtual Tv& vertex(int) = 0;           //顶点v的数据(该顶点确实存在)
    virtual int inDegree(int) = 0;         //定点v的入度(该顶点确实存在)
    virtual int outDegree(int) = 0;        //定点v的出度(该顶点确实存在)
    virtual int firstNbr(int) = 0;         //顶点v的首个邻接顶点
    virtual int nextNbr(int, int) = 0;     //顶点v的(相对于顶点j的)下一邻接顶点
    virtual VStatus& status(int) = 0;      //顶点v的状态i
    virtual int& dTime(int) = 0;           //顶点v的时间标签dTime
    virtual int& fTime(int) = 0;           //顶点v的时间标签fTime
    virtual int& parent(int) = 0;          //顶点v在遍历树中的父亲
    virtual int& priority(int) = 0;        //顶点v在遍历树中的优先级数
//边:这里约定,无向边均统一转化为方向互逆的一对有向边,从而将无向图视作有向图的特例
    int e{};                                 //边总数
    virtual bool exists(int , int ) = 0;   //边(v,u)是否存在
    virtual void insert(Te const&, int, int, int) = 0; //在顶点v,u之间插入权重为w的边e
    virtual Te remove(int, int) = 0;       //删除顶点v,u之间的边e,返回该边的信息
    virtual EType& type(int, int) = 0;     //边(v,u)的类型
    virtual Te& edge(int, int) = 0;        //边(v,u)的数据(该边确实存在)
    virtual int& weight(int, int) = 0;     //边(v,u)的权重
//算法
    void bfs(int);                         //广度优先搜索算法
    void dfs(int);                         //深度优先搜索算法
    void bcc(int);                         //基于DFS的双联通搜索算法
    Stack<Tv> tSort(int);                  //基于DFS的拓扑排序算法
    void prim(int);                        //最小支撑树Prim算法
    void dijkstra(int);                    //最短路径Dijkstra算法
    template<typename PU>                  //优先级搜索框架
    void pfs(int, PU);
};




template<typename Tv>
struct Vertex {                            //顶点对象(为简化起见,未严格封装)
    Tv data;                               //数据,出入度数,状态
    int inDegree;
    int outDegree;
    VStatus status;
    int dTime;                             //时间标签
    int fTime;
    int parent;                            //在遍历树中的父节点,优先级数
    int priority;
    explicit Vertex(Tv const& d = (Tv)0) :          //构造新顶点
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}   //暂时不考虑权重溢出
};

template<typename Te>
struct Edge{                               //边对象(为简化起见,未严格封装)
    Te data;                               //数据,权重,类型
    int weight;
    EType type;
    Edge(Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) {} //构造
};




template<typename Tv, typename Te>         //顶点类型,边类型
class GraphMatrix : public Graph<Tv, Te> { //基于向量,一邻接矩阵形式实现的图
private:
    Vector<Vertex<Tv>> V;                  //顶点集(向量)
    Vector<Vector<Edge<Te>*>> E;           //边集(向量)
public:
    GraphMatrix() {                        //构造
        this->n = this->e = 0;
    }
    ~GraphMatrix() {                       //析构
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                delete E[i][j];
            }
        }
    }
//顶点的基本操作:查询第i个定点(0 <= i < n)
    virtual Tv &vertex(int i) {            //数据
        return V[i].data;
    }
    virtual int inDegree(int i) {          //入度
        return V[i].inDegree;
    }
    virtual int outDegree(int i) {         //出度
        return V[i].outDegree;
    }
    virtual int firstNbr(int i) {          //首个邻接顶点
        return nextNbr(i, this->n);
    }
    virtual int nextNbr(int i, int j) {    //相对与顶点j的下一邻接顶点(改用邻接表可提高效率)
        while ((-1 < j) && (!exists(i, --j))); //逆向线性试探
        return j;
    }
    virtual VStatus& status(int i) {       //状态
        return V[i].status;
    }
    virtual int& dTime(int i) {            //时间标签dTime
        return V[i].dTime;
    }
    virtual int& fTime(int i) {            //时间标签fTime
        return V[i].fTime;
    }
    virtual int& parent(int i) {           //在遍历树中的父亲
        return V[i].parent;
    }
    virtual int& priority(int i) {         //在遍历树中的优先级数
        return V[i].priority;
    }
//顶点的动态操作
    virtual int insert(Tv const& vertex) { //插入顶点,返回编号
        for (int i = 0; i < this->n; i++) {//各顶点预留一条潜在的关联边
            E[i].insert(nullptr);
        }
        (this->n)++;
        E.insert(Vector<Edge<Te>*>(this->n, this->n, (Edge<Te>*) nullptr)); //创建新顶点对应的边向量
        return V.insert(Vertex<Tv> (vertex));//顶点向量增加一个顶点
    }
    virtual Tv remove(int i) {             //删除第i个顶点以及其关联边(0 <= i < n)
        for (int j = 0; j < this->n; j++) {//所有出边
            if (exists(i, j)) {            //逐条删除
                delete E[i][j];
                V[j].inDegree--;
            }
        }
        E.remove(i);                       //删除第i行
        (this->n)--;
        Tv vBak = vertex(i);               //删除顶点i
        V.remove(i);
        for (int j = 0; j < this->n; j++) {//所有入边
            if (Edge<Te>* e = E[j].remove(i)) {//逐条删除
                delete e;
                V[j].outDegree--;
            }
        }
        return vBak;                       //返回被删除顶点信息
    }
//边的确认操作
    virtual bool exists(int i, int j) {    //边(i,j)是否存在
        return (0 <= i) && (i < this->n) && (0 <= j) && (j < this->n) && E[i][j] != nullptr;
    }
//边的基本操作:查询顶点i,j之间的联边(0 <= i, j < n && exists(i, j))
    virtual EType& type(int i, int j) {    //边(i,j)的类型
        return E[i][j]->type;
    }
    virtual Te& edge(int i, int j) {       //边(i,j)的数据
        return E[i][j]->data;
    }
    virtual int& weight(int i, int j) {    //边(i,j)的权重
        return E[i][j]->weight;
    }
//边的动态操作
    virtual void insert(Te const& edge, int w, int i, int j) { //插入权重为w的边e = (i,j)
        if (exists(i, j)) {                //确保该边尚不存在
            return ;
        }
        E[i][j] = new Edge<Te> (edge, w);  //创建新边
        (this->e)++;
        V[i].outDegree++;                  //更新技术与关联顶点的度数
        V[j].inDegree++;
    }
    virtual Te remove(int i, int j) {      //删除定点i,j之间的关联边
        Te eBak = edge(i, j);              //备份后删除记录
        delete E[i][j];
        E[i][j] = nullptr;
        (this->e)--;                       //更新边基数与关联顶点的度数
        V[i].outDegree--;
        V[j].inDegree--;
        return eBak;                       //返回被删除边的信息
    }
};



#endif //GRAPH_GRAPH_H

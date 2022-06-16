//
// Created by wjy on 22-6-15.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include "../Stack/Stack.h"
#include "../Vector/Vector.h"

#define INT_MAX 2e10

typedef enum {                        //����״̬
    UNDISCOVERED, DISCOVERED, VISITED
} VStatus;

typedef enum {                        //���ڱ�����������������
    UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
} EType;

template<typename Tv, typename Te> //��������
class Graph{                       //ͼGraphģ����
private:
    void reset() {                 //���ж���,�ߵĸ�����Ϣ��λ
        for (int i = 0; i < n; i++) {      //���ж����
            status(i) = UNDISCOVERED;      //״̬
            dTime(i) = fTime(i) = -1;      //ʱ���ǩ
            parent(i) = -1;                //(�ڱ������е�)���ڵ�
            priority(i) = INT_MAX;         //���ȼ���
            for (int j = 0; j < n; j++) {  //���бߵ�
                if (exists(i, j)) {
                    type(i, j) = UNDETERMINED; //����
                }
            }
        }
    }
    void BFS(int , int&);                  //(��ͨ��)��������㷨
    void DFS(int , int&);                  //(��ͨ��)��������㷨
    void BCC(int , int& , Stack<int>&);    //(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
    bool TSort(int , int& , Stack<Tv>*);   //(��ͨ��)����DFS�����������㷨
    template<typename PU>                  //(��ͨ��)���ȼ��������
    void PFS(int, PU);
public:
//����
    int n{};                                 //��������
    virtual int insert(Tv const&) = 0;     //���붨��,���ر��
    virtual Tv remove(int) = 0;            //ɾ�������Լ��������,���ظö�����Ϣ
    virtual Tv& vertex(int) = 0;           //����v������(�ö���ȷʵ����)
    virtual int inDegree(int) = 0;         //����v�����(�ö���ȷʵ����)
    virtual int outDegree(int) = 0;        //����v�ĳ���(�ö���ȷʵ����)
    virtual int firstNbr(int) = 0;         //����v���׸��ڽӶ���
    virtual int nextNbr(int, int) = 0;     //����v��(����ڶ���j��)��һ�ڽӶ���
    virtual VStatus& status(int) = 0;      //����v��״̬i
    virtual int& dTime(int) = 0;           //����v��ʱ���ǩdTime
    virtual int& fTime(int) = 0;           //����v��ʱ���ǩfTime
    virtual int& parent(int) = 0;          //����v�ڱ������еĸ���
    virtual int& priority(int) = 0;        //����v�ڱ������е����ȼ���
//��:����Լ��,����߾�ͳһת��Ϊ�������һ�������,�Ӷ�������ͼ��������ͼ������
    int e{};                                 //������
    virtual bool exists(int , int ) = 0;   //��(v,u)�Ƿ����
    virtual void insert(Te const&, int, int, int) = 0; //�ڶ���v,u֮�����Ȩ��Ϊw�ı�e
    virtual Te remove(int, int) = 0;       //ɾ������v,u֮��ı�e,���ظñߵ���Ϣ
    virtual EType& type(int, int) = 0;     //��(v,u)������
    virtual Te& edge(int, int) = 0;        //��(v,u)������(�ñ�ȷʵ����)
    virtual int& weight(int, int) = 0;     //��(v,u)��Ȩ��
//�㷨
    void bfs(int);                         //������������㷨
    void dfs(int);                         //������������㷨
    void bcc(int);                         //����DFS��˫��ͨ�����㷨
    Stack<Tv> tSort(int);                  //����DFS�����������㷨
    void prim(int);                        //��С֧����Prim�㷨
    void dijkstra(int);                    //���·��Dijkstra�㷨
    template<typename PU>                  //���ȼ��������
    void pfs(int, PU);
};




template<typename Tv>
struct Vertex {                            //�������(Ϊ�����,δ�ϸ��װ)
    Tv data;                               //����,�������,״̬
    int inDegree;
    int outDegree;
    VStatus status;
    int dTime;                             //ʱ���ǩ
    int fTime;
    int parent;                            //�ڱ������еĸ��ڵ�,���ȼ���
    int priority;
    explicit Vertex(Tv const& d = (Tv)0) :          //�����¶���
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}   //��ʱ������Ȩ�����
};

template<typename Te>
struct Edge{                               //�߶���(Ϊ�����,δ�ϸ��װ)
    Te data;                               //����,Ȩ��,����
    int weight;
    EType type;
    Edge(Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) {} //����
};




template<typename Tv, typename Te>         //��������,������
class GraphMatrix : public Graph<Tv, Te> { //��������,һ�ڽӾ�����ʽʵ�ֵ�ͼ
private:
    Vector<Vertex<Tv>> V;                  //���㼯(����)
    Vector<Vector<Edge<Te>*>> E;           //�߼�(����)
public:
    GraphMatrix() {                        //����
        this->n = this->e = 0;
    }
    ~GraphMatrix() {                       //����
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                delete E[i][j];
            }
        }
    }
//����Ļ�������:��ѯ��i������(0 <= i < n)
    virtual Tv &vertex(int i) {            //����
        return V[i].data;
    }
    virtual int inDegree(int i) {          //���
        return V[i].inDegree;
    }
    virtual int outDegree(int i) {         //����
        return V[i].outDegree;
    }
    virtual int firstNbr(int i) {          //�׸��ڽӶ���
        return nextNbr(i, this->n);
    }
    virtual int nextNbr(int i, int j) {    //����붥��j����һ�ڽӶ���(�����ڽӱ�����Ч��)
        while ((-1 < j) && (!exists(i, --j))); //����������̽
        return j;
    }
    virtual VStatus& status(int i) {       //״̬
        return V[i].status;
    }
    virtual int& dTime(int i) {            //ʱ���ǩdTime
        return V[i].dTime;
    }
    virtual int& fTime(int i) {            //ʱ���ǩfTime
        return V[i].fTime;
    }
    virtual int& parent(int i) {           //�ڱ������еĸ���
        return V[i].parent;
    }
    virtual int& priority(int i) {         //�ڱ������е����ȼ���
        return V[i].priority;
    }
//����Ķ�̬����
    virtual int insert(Tv const& vertex) { //���붥��,���ر��
        for (int i = 0; i < this->n; i++) {//������Ԥ��һ��Ǳ�ڵĹ�����
            E[i].insert(nullptr);
        }
        (this->n)++;
        E.insert(Vector<Edge<Te>*>(this->n, this->n, (Edge<Te>*) nullptr)); //�����¶����Ӧ�ı�����
        return V.insert(Vertex<Tv> (vertex));//������������һ������
    }
    virtual Tv remove(int i) {             //ɾ����i�������Լ��������(0 <= i < n)
        for (int j = 0; j < this->n; j++) {//���г���
            if (exists(i, j)) {            //����ɾ��
                delete E[i][j];
                V[j].inDegree--;
            }
        }
        E.remove(i);                       //ɾ����i��
        (this->n)--;
        Tv vBak = vertex(i);               //ɾ������i
        V.remove(i);
        for (int j = 0; j < this->n; j++) {//�������
            if (Edge<Te>* e = E[j].remove(i)) {//����ɾ��
                delete e;
                V[j].outDegree--;
            }
        }
        return vBak;                       //���ر�ɾ��������Ϣ
    }
//�ߵ�ȷ�ϲ���
    virtual bool exists(int i, int j) {    //��(i,j)�Ƿ����
        return (0 <= i) && (i < this->n) && (0 <= j) && (j < this->n) && E[i][j] != nullptr;
    }
//�ߵĻ�������:��ѯ����i,j֮�������(0 <= i, j < n && exists(i, j))
    virtual EType& type(int i, int j) {    //��(i,j)������
        return E[i][j]->type;
    }
    virtual Te& edge(int i, int j) {       //��(i,j)������
        return E[i][j]->data;
    }
    virtual int& weight(int i, int j) {    //��(i,j)��Ȩ��
        return E[i][j]->weight;
    }
//�ߵĶ�̬����
    virtual void insert(Te const& edge, int w, int i, int j) { //����Ȩ��Ϊw�ı�e = (i,j)
        if (exists(i, j)) {                //ȷ���ñ��в�����
            return ;
        }
        E[i][j] = new Edge<Te> (edge, w);  //�����±�
        (this->e)++;
        V[i].outDegree++;                  //���¼������������Ķ���
        V[j].inDegree++;
    }
    virtual Te remove(int i, int j) {      //ɾ������i,j֮��Ĺ�����
        Te eBak = edge(i, j);              //���ݺ�ɾ����¼
        delete E[i][j];
        E[i][j] = nullptr;
        (this->e)--;                       //���±߻������������Ķ���
        V[i].outDegree--;
        V[j].inDegree--;
        return eBak;                       //���ر�ɾ���ߵ���Ϣ
    }
};



#endif //GRAPH_GRAPH_H

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

template<typename Tv, typename Te> //�����������BFS�㷨(ȫͼ)
void Graph<Tv,Te>::bfs(int s) {    //0 <= s < n
    reset();                       //��ʼ��
    int clock = 0;
    int v = s;
    do {                           //��һ������ж���
        if (UNDISCOVERED == status(v)) { //һ��������δ���ֵĶ���
            BFS(v, clock);      //���Ӹö����������һ��BFS
        }
    } while (s != (v = (++v % n)));//����ż��,�ʲ�©����
}

template<typename Tv, typename Te> //�����������BFS�㷨(������ͨ��)
void Graph<Tv, Te>::BFS(int v, int &clock) { //0 <= v < n
    Queue<int> Q;                  //���븨������
    status(v) = DISCOVERED;        //��ʼ�����
    Q.enqueue(v);
    while (!Q.empty()) {           //��Q���֮ǰ,����
        int v_temp = Q.dequeue();  //ȡ�����׶���v_temp
        dTime(v_temp) = ++clock;
        for (int u = firstNbr(v_temp); -1 < u; u = nextNbr(v_temp, u)) { //ö��v�������ھ�
            if (UNDISCOVERED == status(u)) { //��u��δ������,��
                status(u) = DISCOVERED;      //���ָö���
                Q.enqueue(u);
                type(v_temp, u) = TREE;      //����������չ֧����
                parent(u) = v_temp;
            } else {                         //��u�Ѿ�������,���������Ѿ��������,��
                type(v_temp, u) = CROSS;     //��(v,u)�����ڿ��
            }
        }
    }
    status(v) = VISITED;                     //����,��ǰ����������
}

template<typename Tv, typename Te> //�����������DFS�㷨(ȫͼ)
void Graph<Tv, Te>::dfs(int s) {   //0 <= s < n
    reset();                       //��ʼ��
    int clock = 0;
    int v = s;
    do {                           //��һ������ж���
        if (UNDISCOVERED == status(v)) { //һ��������δ���ֵĶ���
            DFS(v, clock);      //���Ӹö����������һ��DFS
        }
    } while (s != (v = (++v % s))); //����ż��,���ز�©
}

template<typename Tv, typename Te> //������������㷨DFS(������ͨ��)
void Graph<Tv, Te>::DFS(int v, int &clock) { //0 <= v < n
    dTime(v) = ++clock;            //���ֵ�ǰ����v
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) { //ö��v�������ھ�
        switch (status(u)) {       //����״̬�ֱ���
            case UNDISCOVERED:     //u��δ����,��ζ��֧�������ڴ���չ
                type(v, u) = TREE;
                parent(u) = v;
                DFS(u, clock);
                break;
            case DISCOVERED:       //u�ѱ����ֵ�δ�������,Ӧ�������ָ�������
                type(v, u) = BACKWARD;
                break;
            default:               //u�ѷ������(VISITED,����ͼ),���ӳ�Ϯ��ϵ�ֱ�Ϊǰ��߻���
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;           //����,��ǰ����v����������
    fTime(v) = ++clock;
}

template<typename Tv, typename Te> //����DFS�����������㷨
Stack<Tv> Graph<Tv, Te>::tSort(int s) { //0 <= s < n
    reset();
    int clock = 0;
    int v = s;
    auto *S = new Stack<Tv>;       //��ջ��¼���򶥵�
    do {
        if (UNDISCOVERED == status(v)) {
            if (!TSort(v, clock, s)) { //clock���Ǳ���
                while (!S->empty()) { //��һ��ͨ��(����ͼ)��DAG
                    S->pop();      //�򲻱ؼ�������,��ֱ�ӷ���
                    break;
                }
            }
        }
    } while (s != (v = (++v % n)));
    return S;                      //������ΪDAG,��S�ڸ������Զ��������,����(��������������),S��
}

template<typename Tv, typename Te> //����DFS�����������㷨(����)
bool Graph<Tv, Te>::TSort(int v, int &clock, Stack<Tv> *S) { //0 <= v < n
    dTime(v) = ++clock;            //���ֶ���v
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {   //ö��v�������ھ�u
        switch (status(u)) {                                 //����u��״̬�ֱ���
            case UNDISCOVERED:
                parent(u) = v;
                type(v, u) = TREE;
                if (!TSort(u, clock, S)) {             //�Ӷ���u������������
                    return false;                            //��u������������������(����ȫͼ���), �ʷ��ز�������
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;                       //һ�����ֺ����(��DAG),��
                return false;                                //��������,�ʷ���������
            default:                                         //VISITED(digraphs only)
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;                                     //���㱻���ΪVISITED��ʱ���漴��ջ
    S->push(vertex(v));
    return true;                                             //v������������������
}

template<typename Tv, typename Te> //����DFS��BCC�ֽ��㷨
void Graph<Tv, Te>::bcc(int s) {
    reset();
    int clock = 0;
    int v = s;
    Stack<int> S;                  //ջS���ڼ�¼�ѷ��ʵĶ���
    do {
        if (UNDISCOVERED == status(v)) { //һ������δ���ֵĶ���
            BCC(v, clock, s);      //���Ӹö����������һ��BCC
            S.pop();                     //�������غ�,����ջ�����һ������--��ǰ��ͨ��Ķ���
        }
    } while (s != (v = ++v % n));
}

#define hca(x) (fTime(x))          //�˴��������õ�fTime[]�䵱hca[]
template<typename Tv, typename Te> //��������,������
void Graph<Tv, Te>::BCC(int v, int &clock, Stack<int> &S) { //0 <= v < n
    hca(v) = dTime(v) = ++clock;                            //v����������ջ
    status(v) = DISCOVERED;
    S.push(v);
    for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {  //ö��v�����ھ�u
        switch (status(u)) {       //��u����ֱ���
            case UNDISCOVERED:
                parent(u) = v;                              //�Ӷ���u������
                type(v, u) = TREE;
                BCC(u, clock, S);
                if (hca(u) < dTime(v)) {                    //�������غ�,������u(ͨ�������)��ָ��v��������
                    hca(v) = min(hca(v), hca(u));     //��v�����
                } else {                                    //����,��vΪ�ؽڵ�(u���¼���һ��BCC,�����ж����ʱ��������ջS����)
                    while (v != S.pop());                   //���ε�����ǰBCC�еĽڵ�,��ɸ���ʵ������ת���������ṹ
                    S.push(v);                           //���һ������(�ؽڵ�)������ջ--��̯����һ��
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;                      //���(v,u),������ԽСԽ�ߵ�ԭ��
                if (u != parent(v)) {
                    hca(v) = min(hca(v), dTime(u));   //����hca(v)
                }
                break;
            default:                                        //VISITED (digraphs only)
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;                //��v�ķ��ʽ���
}

//��������,������,���ȼ�������
template<typename Tv, typename Te> template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) { //���ȼ�����(������ͨ��)
    reset();                                     //��ʼ��,s��ӵ�PFS����
    int v = s;
    do {                        //��һ������ж���
        if (UNDISCOVERED == status(v)) { //һ��������δ�����Ķ���
            PFS(v, prioUpdater);      //�ʹӸö����������һ��PFS
        }
    } while (s != (v = (++v % n)));      //����ż��,���ز�©
}

//��������,������,���ȼ�������
template<typename Tv, typename Te> template<typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) { //���ȼ�����(������ͨ��)
    priority(s) = 0;                             //��ʼ��,s��ӵ�PFS����
    status(s) = VISITED;
    parent(s) = -1;
    while (true) {                               //����һ����ͱ߼ӵ�PFS����
        for (int w = firstNbr(s); w > -1; w = nextNbr(s, w)) { //ö�������ھ�w
            prioUpdater(this, s, w);             //���¶���w�����ȼ��Լ��丸�ڵ�
        }
        for (int shortest = INT_MAX, w = 0; w < n; w++) {
            if (UNDISCOVERED == status(w)) {     //����δ����������Ķ�����
                if (shortest > priority(w)) {    //ѡ����һ��
                    shortest = priority(w);      //���ȼ���ߵĶ���s
                    s = w;
                }
            }
        }
        if (VISITED == status(s)) {              //ֱ�����ж��㶼�Ѿ�����
            break;
        }
        status(s) = VISITED;                     //��s���丸�ڵ�����߼��������
        type(parent(s), s) = TREE;
    }
}                   //ͨ�������������ȼ����²���prioUpdater,����ʵ�ֲ�ͬ���㷨����

template<typename Tv, typename Te>               //���Dijkstra�㷨�Ķ������ȼ�������
struct DijkstraPU {
            virtual void operator() (Graph<Tv,Te>* g, int uk, int v) { //����ukÿһ��δ�����ֵ��ڽӶ���v,��Dijkstra����
                if (UNDISCOVERED == g->status(v)) {
                    if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) { //���ɳ�
                        g->priority(v) = g->priority(uk) + g->weight(uk, v);   //�������ȼ���
                        g->parent(v) = uk; //��ͬʱ���¸��ڵ�
                    }
                }
            }
        };

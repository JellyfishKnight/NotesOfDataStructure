//
// Created by wjy on 22-6-15.
//

#include "Graph.h"
#include "../Vector/Vector.h"
#include "../Queue/Queue.h"

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
    } while (s != (v == (++v % s))); //����ż��,���ز�©
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
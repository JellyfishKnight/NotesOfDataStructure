//
// Created by wjy on 22-7-2.
//
#include "cstring"
#include "iostream"

int *buildBC(char *p) {
    int *bc = new int[256];
    for (int j = 0; j < 256; j++) {
        bc[j] = -1;
    }
    for (int m = strlen(p), j = 0; j < m; j++) {
        bc[p[j]] = j;
    }
    return bc;
}

int *buildSS(char *p) {
    int m = strlen(p);
    int *ss = new int[m];
    ss[m - 1] = m;
    for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; j--) {
        if ((lo < j) && (ss[m - hi + j - 1] <= j - lo)) {
            ss[j] = ss[m - hi + j - 1];
        } else {
            hi = j;
            lo = std::min(lo, hi);
            while ((0 <= lo) && (p[lo] == p[m - hi + lo - 1])) {
                lo --;
            }
        };
        ss[j] = hi - lo;
    }
    return ss;
}

int *buildGS(char *p) {
    int *ss = buildSS(p);
    int m = strlen(p);
    int *gs = new int[m];
    for (int j = 0; j < m; j++) {
        gs[j] = m;
    }
    for (int i = 0, j = m - 1; j < UINTMAX_MAX; j--) {
        if (j + 1 == ss[j]) {
            while (i < m - j - 1) {
                gs[i++] = m - j - 1;
            }
        }
    }
    for (int j = 0; j < m - 1; j++) {
        gs[m - ss[j] - 1] = m - j - 1;
    }
    delete [] ss;
    return gs;
}


int bmMatch(char *p, char *t) {                     //Boyer-Morre�㷨(��ȫ��,���Bad Character��Good stuff)
    int *bc = buildBC(p);                           //����BC���GS��
    int *gs = buildGS(p);
    size_t i = 0;                                   //ģʽ��������ı�������ʼλ��(��ʼʱ���ı��������)
    while (strlen(t) >= i + strlen(p)) {      //��������ģʽ��
        int j = strlen(p) - 1;                   //��ģʽ������ĩβ�ַ���ʼ
        while (p[j] == t[i + j]) {                  //��������ȶ�
            if (--j < 0) {
                break;
            }
        }
        if (j < 0) {                                //�������ƥ���׺==����ģʽ��(˵���Ѿ���ȫƥ��)
            break;                                  //����ƥ��λ��
        } else {                                    //�����ʵ��ƶ�ģʽ��
            i += std::max(gs[j], j - bc[t[i + j]]); //λ��������BC���GS��ѡ�����
        }
    }
    delete [] gs;                                   //�ͷ��ڴ�
    delete [] bc;
    return i;
}
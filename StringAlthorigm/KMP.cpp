//
// Created by wjy on 22-7-2.
//
#include "cstring"

int *buildNext(char *p) {            //����ģʽ��p��next��
    size_t m = strlen(p), j = 0;  //"��"��ָ��
    int *n = new int[m];             //next��
    int t = n[0]  -1;                //ģʽ��ָ��
    while (j < m - 1) {
        if (t < 0 || p[j] == p[t]) { //ƥ��
            j++;
            t++;
            n[j] = t;
        } else {                     //ʧ��
            t = n[t];
        }
    }
    return n;
}


int match(char *p, char *t) {           //KMP�㷨
    int *next = buildNext(p);           //����next��
    int n = (int) strlen(t), i = 0;  //�ı���ָ��
    int m = (int) strlen(p), j = 0;  //ģʽ��ָ��
    while (j < m && i < n) {            //����������ȶ��ַ�
        if (0 > j || t[i] == p[j]) {    //���ƥ��,����p�����Ƴ������(�����жϵĴ��򲻿ɽ���)
            i++;                        //��ת����һ�ַ�
            j++;
        } else {
            j = next[j];                //����ģʽ������
        }
    }
    delete [] next;                     //�ͷ�next��
    return i - j;
}
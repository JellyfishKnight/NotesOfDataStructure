//
// Created by wjy on 22-7-2.
//
#include "cstring"


/*未改进版*/
//int *buildNext(char *p) {            //构造模式串p的next表
//    size_t m = strlen(p), j = 0;  //"主"串指针
//    int *n = new int[m];             //next表
//    int t = n[0]  -1;                //模式串指针
//    while (j < m - 1) {
//        if (t < 0 || p[j] == p[t]) { //匹配
//            j++;
//            t++;
//            n[j] = t;
//        } else {                     //失配
//            t = n[t];
//        }
//    }
//    return n;
//}
/*改进版*/
int *buildNext(char *p) {
    size_t m = strlen(p), j = 0;
    int *n = new int[m];
    int t = n[0] = -1;
    while (j < m - 1) {
        if (t < 0 || p[j] == n[t]) {
            j++;
            t++;
            n[j] = (p[j] != p[t]) ? t : n[t]; //注意此句与未改进版的差别
        } else {
            t = n[t];
        }
    }
    return n;
}


int kmpMatch(char *p, char *t) {           //KMP算法
    int *next = buildNext(p);           //构造next表
    int n = (int) strlen(t), i = 0;  //文本串指针
    int m = (int) strlen(p), j = 0;  //模式串指针
    while (j < m && i < n) {            //从左到右逐个比对字符
        if (0 > j || t[i] == p[j]) {    //如果匹配,或者p己经移出最左侧(两个判断的次序不可交换)
            i++;                        //就转到下一字符
            j++;
        } else {
            j = next[j];                //否则模式串右移
        }
    }
    delete [] next;                     //释放next表
    return i - j;
}
//
// Created by wjy on 22-7-2.
//
#include "iostream"
#include "cstring"


//±©¡¶À„∑®
int match(char *p, char *t) {
    size_t n = strlen(t), i = 0;
    size_t m = strlen(p), j;
    for (i = 0; i < n - m + 1; i++) {
        for (j = 0; j < m; j++) {
            if (t[i + j] != p[j]) {
                break;
            }
        }
        if (j >= m) {
            break;
        }
    }
    return i;
}
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


int bmMatch(char *p, char *t) {                     //Boyer-Morre算法(完全版,兼顾Bad Character和Good stuff)
    int *bc = buildBC(p);                           //构造BC表和GS表
    int *gs = buildGS(p);
    size_t i = 0;                                   //模式串相对于文本串的起始位置(初始时与文本串左对齐)
    while (strlen(t) >= i + strlen(p)) {      //不断右移模式串
        int j = strlen(p) - 1;                   //从模式串的最末尾字符开始
        while (p[j] == t[i + j]) {                  //从右向左比对
            if (--j < 0) {
                break;
            }
        }
        if (j < 0) {                                //如果极大匹配后缀==整个模式串(说明已经完全匹配)
            break;                                  //返回匹配位置
        } else {                                    //否则适当移动模式串
            i += std::max(gs[j], j - bc[t[i + j]]); //位移量根据BC表和GS表选择大者
        }
    }
    delete [] gs;                                   //释放内存
    delete [] bc;
    return i;
}
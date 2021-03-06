//
// Created by wjy on 22-6-17.
//
#include "Stack.h"

void convert_reverse(Stack<char>& s, int n, int base) {            //十进制正整数n到base进制的转换
    static char digit[] = {                                //0 < n, 1 < base <= 16
            '0', '1', '2', '3', '4', '5',
            '6', '7', '8', '9', 'A',
            'B', 'C', 'D', 'E', 'F'
    };
    if (0 < n) {                         //在尚有余数之前,反复地
        s.push(digit[n % base]);      //逆向记录当前的最低位, 再
        convert_reverse(s, n / base, base); //通过递归得到所有更高位
    }
}                                      //新进制下由高到底的各数位,自顶向下存于栈s中

void convert_range(Stack<char>& s, int n, int base) {               //十进制转任意进制(迭代版)
    static char digit[] = {                                //0 < n, 1 < base <= 16
            '0', '1', '2', '3', '4', '5',
            '6', '7', '8', '9', 'A',
            'B', 'C', 'D', 'E', 'F'
    };
    while (n > 0) {
        s.push(digit[n % base]);
        n /= base;
    }
}

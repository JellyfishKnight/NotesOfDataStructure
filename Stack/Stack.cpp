//
// Created by wjy on 22-6-17.
//
#include "Stack.h"

void convert_reverse(Stack<char>& s, int n, int base) {            //ʮ����������n��base���Ƶ�ת��
    static char digit[] = {                                //0 < n, 1 < base <= 16
            '0', '1', '2', '3', '4', '5',
            '6', '7', '8', '9', 'A',
            'B', 'C', 'D', 'E', 'F'
    };
    if (0 < n) {                         //����������֮ǰ,������
        s.push(digit[n % base]);      //�����¼��ǰ�����λ, ��
        convert_reverse(s, n / base, base); //ͨ���ݹ�õ����и���λ
    }
}                                      //�½������ɸߵ��׵ĸ���λ,�Զ����´���ջs��

void convert_range(Stack<char>& s, int n, int base) {               //ʮ����ת�������(������)
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

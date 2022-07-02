#include <iostream>
#include "Vector.h"
#include "../Vector/Vector.cpp"

using namespace std;

int main() {
	Vector<int> v;
    v.insert(1);
    v.insert(3);
    v.insert(2);
    v.insert(1);
    v.insert(7);
    v.quickSort(1, 5);
    for (Rank i = 0; i < 5; i++) {
        cout << v[i] ;
    }
	return 0;
}

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    for (auto &item: a) {
        cin >> item;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    for (const auto &item: a) {
        cout << item << " " ;
    }
    return 0;
}
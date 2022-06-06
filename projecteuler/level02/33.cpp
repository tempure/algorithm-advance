#include<bits/stdc++.h>
using namespace std;

//谜语题，暴力枚举
//https://blog.csdn.net/pfccWang/article/details/78039579
//ans = 100

int main() {
    int fz = 1, fm = 1;
    for (int i = 1; i <= 9; i++) {
        for (int j = i + 1; j <= 9; j++) {
            for (int k = i; k <= 9; k++) {
                if (j * (i * 10 + k) == i * (j * 10 + k)) {
                    fz *= i;
                    fm *= j;
                }
                else if (j * (i * 10 + k) == i * (k * 10 + j)) {
                    fz *= i;
                    fm *= j;
                }
                else if (j * (k * 10 + i) == i * (j * 10 + k)) {
                    fz *= i;
                    fm *= j;
                }
                else if (j * (k * 10 + i) == i * (k * 10 + j)) {
                    fz *= i;
                    fm *= j;
                }
            }
        }
    }
    cout << fm / __gcd(fz, fm) << endl;
    return 0;
}
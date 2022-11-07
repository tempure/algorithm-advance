#include<bits/stdc++.h>
using namespace std;

//暴力

int prime[10] = {0, 2, 3, 5, 7, 11, 13, 17, 19,};

int main() {
    int num[11] = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9,};
    int maxn = 3628800 - 362880;
    long long ans = 0;
    for (int boolean = 1, i = 1; i <= maxn; boolean = 1, i++) {
        for (int tmp = 0, j = 1; j < 8 && boolean; tmp = 0, j++) {
            for (int k = j; k <= j + 2; k++) {
                tmp = tmp * 10 + num[k];
            }
            if (tmp % prime[j] != 0) {boolean = 0; break;}
        }
        if (boolean) {
            long long tmp = 0;
            for (int j = 0; j < 10; j++) {
                tmp = tmp * 10 + num[j];
            }
            cout << tmp << endl;
            ans += tmp;
        }
        next_permutation(num, num + 10);
    }
    cout << ans << endl;
    return 0;
}
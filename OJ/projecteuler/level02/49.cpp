#include<bits/stdc++.h>
using namespace std;

int num[6];
int prime[10010], boolean[10010], cnt;

//暴力check 所有四位数
//ans = 296962999629

void check() {
    int x[25], cnt = 0;
    for (int i = 1; i <= 24; i++) { //4! = 24 所有排列
        int tmp = 0;
        for (int j = 1; j <= 4; j++) {
            tmp = tmp * 10 + num[j];
        }
        if (!boolean[tmp] && tmp >= 1000)   x[++cnt] = tmp;
        next_permutation(num + 1, num + 5);
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = i + 1; j <= cnt; j++) {
            if (x[j] == x[i]) continue; //必须是3个不同的质数
            for (int k = j + 1; k <= cnt; k++) {
                if (x[k] + x[i] == x[j] + x[j])
                    cout << x[i] << x[j] << x[k] << endl;
            }
        }
    }
}

int main() {
    boolean[1] = 1;
    for (int i = 2; i <= 9999; i++) {
        if (!boolean[i])    prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= 9999; j++) {
            boolean[i * prime[j]] = true;
        }
    }
    for (int i = 0; i <= 9; i++) {
        num[1] = i;
        for (int j = i; j <= 9; j++) {
            num[2] = j;
            for (int k = j; k <= 9; k++) {
                num[3] = k;
                for (int l = k; l <= 9; l++) {
                    num[4] = l;
                    check();
                }
            }
        }
    }
    return 0;
}
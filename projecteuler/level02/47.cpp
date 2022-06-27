#include<bits/stdc++.h>
using namespace std;

//尝试在前1e6里面暴力
//先筛素数然后逐个判断
//ans = 134043

const int maxn = 999999;
int prime[maxn + 10], num[maxn + 10], cnt;
int fact;

int main() {
    num[1] = 0;
    for (int i = 2; i <= maxn; i++) {
        if (num[i] == 0)  prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= maxn; j++) {
            num[i * prime[j]] = 1;
        }
    }
    int x = 0;
    for (int i = 1; i <= maxn; i++) {
        int tmp = i;
        fact = 0;
        for (int j = 1; prime[j]*prime[j] <= tmp; j++) {
            if (tmp % prime[j] == 0)        fact++;
            while (tmp % prime[j] == 0)  tmp /= prime[j];
        }
        if (tmp != 1)     fact++;
        if (fact == 4)    x++;
        else            x = 0;
        if (x == 4) {
            cout << i - 3 << endl;
            return 0;
        }
    }
}
#include<bits/stdc++.h>
using namespace std;

const int maxn = 10000000;
int prime[maxn + 1], cnt;
int num[maxn + 1];


//线性筛+check
//上界未知，筛1kw尝试

// ans = 748317

bool check(int x) {
    for (int i = 10; i / 10 < x; i *= 10) {
        if (num[x % i])   return false;
    }
    while (x) {
        if (num[x]) return false;
        x /= 10;
    }
    return true;
}

int main() {
    cnt = 0;
    num[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        if (num[i] == 0)   prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= maxn; j++) {
            num[i * prime[j]] = 1;
        }
    }
    int n = 0, ans = 0;
    for (int i = 5; n < 11; i++) {
        if (check(prime[i])) {
            n++; ans += prime[i];
        }
    }
    cout << ans << endl;
    return 0;
}
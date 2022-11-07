#include<bits/stdc++.h>
using namespace std;

const int maxn = 1000000;
int prime[maxn + 1], cnt;
int num[maxn + 1];

//先用线性筛求出所有素数，之后对每个素数进行验证
//ans = 55

bool check(int x) {
    int mul = 1;
    while (mul <= x)   mul *= 10;
    mul /= 10;
    int tmp = x;
    do {
        if (tmp % 10 == 0)  return false;
        tmp = tmp / 10 + tmp % 10 * mul;
        if (num[tmp])   return false;
    } while (tmp != x);
    return true;
}

int main() {
    int ans = 0;
    for (int i = 2; i <= maxn; i++) {
        if (num[i] == 0)   {
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= maxn; j++) {
            num[i * prime[j]] = 1;
        }
    }
    for (int i = 1; i <= cnt; i++) {
        if (check(prime[i])) {
            cout << prime[i] << endl;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
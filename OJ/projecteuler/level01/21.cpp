#include <bits/stdc++.h>
using namespace std;

//哦这个题意好迷。。。。

int d[10001];

int main() {
    int n = 10000;
    for (int i = 1; i <= n; i++) {
        for (int j = i * 2; j <= n; j += i) {
            d[j] += i;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i] != i && d[i] <= n && d[d[i]] == i) {
            ans += i;
        }
    }
    cout << ans << endl;
    return 0;
}
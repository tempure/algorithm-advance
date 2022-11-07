#include <bits/stdc++.h>
using namespace std;

//https://codeforces.com/blog/entry/100780
//DP就是类似于完全背包，处理因子
//分类讨论的做法也挺麻烦的。。。

int prime(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0)
            return i;
    }
    return -1;
}

void solve() {
    int x, d;
    cin >> x >> d;
    int cnt = 0;
    while (x % d == 0) {
        ++cnt;
        x /= d;
    }
    if (cnt == 1) {
        cout << "NO\n";
        return;
    }
    if (prime(x) != -1) {
        cout << "YES\n";
        return;
    }
    if (prime(d) != -1 && d == prime(d) * prime(d)) {
        if (x == prime(d) && cnt == 3) {
            cout << "NO\n";
            return;
        }
    }
    if (cnt > 2 && prime(d) != -1) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
        solve();
}
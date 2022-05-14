#include <bits/stdc++.h>
using namespace std;
#define int long long

//Matrix chain multiplication 矩阵链乘积
//https://zh.wikipedia.org/wiki/%E7%9F%A9%E9%99%A3%E9%8F%88%E4%B9%98%E7%A9%8D
//https://blog.csdn.net/qq_43427808/article/details/109195977
//https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_B  模板题

const int N = 110;
int p[N], m[N][N], s[N][N];

int Matrix_Chain_Order(int p[], int n) {
    for (int l = 2; l <= n; l++) { // l is chain length
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]; //Matrix Ai has the dimension  p[i-1] x p[i].
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[1][n];
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i - 1] >> p[i];
    }
    cout << Matrix_Chain_Order(p, n) << endl;
}

signed main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

/*
不取模求组合数C(m, n)
递推法复杂度O(n*m*k),k是高精度计算的位数，可以当作常数

也可以筛质数+分解质因数+高精度乘法 但是太麻烦了
*/
const int N = 150;
int k, x;
int f[1000][100][N];

int qmi(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void add(int c[], int a[], int b[]) {
    for (int i = 0, t = 0; i < N; i++) {
        t += a[i] + b[i];
        c[i] = t % 10;
        t /= 10;
    }
}

void solve() {
    cin >> k >> x;
    int n = qmi(x % 1000, x, 1000);

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i && j < k; j++)
            if (!j) f[i][j][0] = 1;
            else add(f[i][j], f[i - 1][j], f[i - 1][j - 1]);
    int *g = f[n - 1][k - 1];
    int i = N - 1;
    while (!g[i]) i --;
    while (i >= 0) cout << g[i--];
}

int main() {
    solve();
    return 0;
}
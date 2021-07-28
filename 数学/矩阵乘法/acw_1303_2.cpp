#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
构造K*K的矩阵，求N项，也就是求矩阵的N次幂，时间复杂度是O(k^3 * log(N))
之前写的时间复杂度注释是错的
*/

const int N = 3;
int n, mod;

void mul(int c[], int a[], int b[][N]) { //c = a  * b
    int temp[3] = {0};
    for (int i = 0; i < N; i++) //列
        for (int j = 0; j < N; j++) //行
            temp[i] = (temp[i] + (ll)a[j] * b[j][i]) % mod;
    memcpy(c, temp, sizeof temp); //这里要写temp  因为传进来的c只是一个指针
}

void mul(int c[][N], int a[][N], int b[][N]) { //c = a * b //二维相乘
    int temp[N][N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                temp[i][j] = (temp[i][j] + (ll)a[i][k] * b[k][j]) % mod;
    memcpy(c, temp, sizeof temp);
}

void solve() {
    cin >> n >> mod;
    int f1[3] = {1, 1, 1,}; //初始1x3矩阵
    int a[3][3] = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 1}
    };

    n --; //递推n-1次
    while (n) {
        if (n & 1) mul(f1, f1, a);
        mul(a, a, a);
        n >>= 1;
    }

    cout << f1[2] << endl;
}

int main() {
    solve();
    return 0;
}
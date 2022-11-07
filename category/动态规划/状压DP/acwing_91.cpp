#include <iostream>
#include <cstring>
using namespace std;

const int N = 20, M = 1 << N ;
int w[N][N];
int f[M][N];  // f[i][j] 表示所有从0走到j 走过的所有点是二进制表示的i的路径 的最短路径

//状态转移方程：f[i][j] = f[i - {j}][k] + w[k][j]  对应路径转移为 k->j , i-{j}是路径中减去j点之后的二进制状态

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> w[i][j];
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0; //最初是第0位 第0位的状态就是1
    for (int i = 0 ; i < 1 << n; i++) //每个状态所依赖的状态，必须在它之前被计算出来
        for (int j = 0; j < n; j++)
            if (i >> j & 1) //当前路径是0~j,那说明必然j对应二进制位是1，才是一个合法状态
                for (int k = 0; k < n; k++) //枚举所有的点 也就是找出倒数第二个点
                    if ((i - (1 << j)) >> k & 1) //枚举所有能到j的点k
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]);

    cout << f[(1 << n) - 1][n - 1] << endl; //1<<n - 1就是全1的状态

    return 0;
}
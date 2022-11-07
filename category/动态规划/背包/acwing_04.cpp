#include <iostream>
using namespace std;

/*
朴素多重背包写法：
相当于是完全背包加了一个限制而已
不一样的地方在于多了每种物品的数量限制而已
方程一样，限制条件不一样
*/

#include <iostream>
using namespace std;

const int N = 110;
int f[N][N], v[N], w[N], s[N];

int main() {
    int n, V;
    cin >> n >> V;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i] >> s[i];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= V; j++)
            for (int k = 0; k <= s[i] && k * v[i] <= j; k++)
                f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);

    cout << f[n][V] << endl;
    return 0;
}
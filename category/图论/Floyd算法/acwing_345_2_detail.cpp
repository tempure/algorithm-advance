#include <bits/stdc++.h>
using namespace std;

//https://www.acwing.com/solution/content/36603/ 题解
//logK*N^3, N是点数，K是题目要求的恰好经过的边数

/*
快速幂的作用：第一次求出所有点之间只经过2条边的最短路，第二次就是4次，第三次就是8次...

本质和Floyd关系不大，变种DP，重点在于开一个tmp数组来保存每次倍增边数得到的最短路径,而不是floyd的同时更新d[][]数组

tmp每次只保存最终的二次幂最短路，完全不会更新g，g要在快速幂mul(g,g,g)中自己更新倍增自己更新

res[i][j] 从i到j经过了恰好k条边的最短路长度,这是最终快速幂分解k后的最终答案

g在mul的过程中每次只保存2的次幂条边数的最短路结果，立用快速幂的思想，将k分解成2的次幂相加的形式，降低枚举的复杂度

做法的正确性：考虑边数为7,用快速幂分解为1+2+4,那么反驳：为什么不分解为3+4,2+5这种分解的方法？
因为所有边数为3的最短路，在快速幂中累加1+2条边的最短路时候，就得到了，同理5也可以分解为1+4，也可以1+2+2，
考虑1+2+2就是1+4，考虑2+1+2这种三段分法的最短路，那么和按照1+4分解的答案完全一致，
所以只是求两点之间的K条边最短路，只需要是k条边就好了，按照任何方式分解路径的边数组合，不会影响最终答案，DP算法的正确性可以保证。

注意不要初始化g[i][i] = 0, 注释有说明，为了防止求不出环的情况
*/

const int N = 210; //边数，点数*2
int g[N][N];
int d[N][N];
int n, m, k, S, E; //n点数 m边数 k恰好经过k条边
int res[N][N]; //答案

void mul(int c[][N], int a[][N], int b[][N]) {
    static int tmp[N][N]; //不 static 也能AC
    memset(tmp, 0x3f, sizeof tmp);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                tmp[i][j] = min(tmp[i][j], a[i][k] + b[k][j]);
    memcpy(c, tmp, sizeof tmp);
}

void qmi() {
    memset(res, 0x3f, sizeof res);
    for (int i = 1; i <= n; i++) res[i][i] = 0;
    while (k) {
        if (k & 1) mul(res, res, g);
        mul(g, g, g);
        k >>= 1;
    }
}

void solve() {
    cin >> k >> m >> S >> E;
    memset(g, 0x3f, sizeof g);
    /*
    不初始化g[i][i] = 0 的原因：
    考虑i->j->i的路径，就是一个二元环，如果g[i][i]=0,那么在mul时候i走到i不论经过多少条边的距离都是0
    无法计算出这种环恰好经过k条边的答案
    */
    map<int, int> ids;
    ids[S] = ++n; //起点和终点
    ids[E] = ++n;
    S = ids[S], E = ids[E];

    while (m --) {
        int a, b, c;
        cin >> c >> a >> b;
        if (!ids.count(a)) ids[a] = ++n; //离散化 点的编号太大 无序离散化即可 只需保持拓扑关系即可
        if (!ids.count(b)) ids[b] = ++n;
        a = ids[a], b = ids[b];
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    qmi();
    cout << res[S][E] << endl;
}

int main() {
    solve();
    return 0;
}
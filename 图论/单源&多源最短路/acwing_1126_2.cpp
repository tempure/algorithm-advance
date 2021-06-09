#include <iostream>
#include <cstring>
using namespace std;

const int N = 2010, M = 2e5 + 10;
int n, m, S, T;
int h[N], e[M], ne[M], idx;
double w[M];
double d[N];
bool v[N];

//稠密图 朴素dijkstra

/*
只有一种情况可以用dijkstra来求最长路，就是原图中的所有边都是负权,有无环无所谓
而且求原图的最长路，其实不能说是“最长”，应该是求和最大的路径

这样把所有边取反后，就是求和最小的路径，也就等价于最短路

这样的性质不仅仅可以加，也可以用来路径的乘积等维护最值都可以
*/

void add(int a, int b, double c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}


void dijkstra() {
    d[S] = 1; //注意是乘积的初始化
    for (int i = 1; i <= n; i++) {
        int t = -1;
        for (int j = 1; j <= n; j++)
            if (!v[j] && (t == -1 || d[t] < d[j]))
                t = j;
        v[t] = true;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (d[j] < d[t] * w[i])
                d[j] = d[t] * w[i];
        }
    }
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    memset(d, 0xcf, sizeof d);
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        double z = (100.0 - c) / 100.0;
        add(a, b, z); add(b, a, z);
    }
    cin >> S >> T;
    dijkstra();
    printf("%.8lf\n", 100.0 / d[T]);

    return 0;
}
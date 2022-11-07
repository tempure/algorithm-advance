#include <iostream>
using namespace std;
//不是带依赖的背包 不一样

//这个是每个连通块看成一个物品 一个连通块内的物品每次都要全部买
//然后对所有连通块做一次01背包

//在求连通块的同时 维护每个连通块的总价钱和总价值  都用父亲节点来计算
//最后01背包时候只需要遍历每个并查集的父节点即可

const int N = 10010;
int vol;
int w[N], v[N];
int p[N];
int f[N];
int n, m;

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

int main() {
    cin >> n >> m >> vol;
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];


    while (m --) {
        int a, b;
        cin >> a >> b;
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            v[pb] += v[pa];
            w[pb] += w[pa];
            p[pa] = pb;
        }
    }

    for (int i = 1; i <= n; i++)
        if (p[i] == i) //注意一定要是DSU的root节点才选择该点进行01背包
            for (int j = vol; j >= v[i]; j --)
                f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[vol] << endl;
    return 0;
}
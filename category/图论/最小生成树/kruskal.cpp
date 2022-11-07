//kruskal 模板
//AcWing 859

#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int n, m, res;
int cnt; //最小生成树的边数量 判断是否无解
int p[N];

struct Edge {
    int a, b, w;
    bool operator<(const Edge &u) {
        return w < u.w;
    }
} edges[M];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void kruskal() {
    sort(edges, edges + m);
    for (int i = 0; i < m; i++) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        a = find(a), b = find(b);
        if (a != b) {
            res += w;
            p[a] = b;
            cnt ++;
        }
    }
    if (cnt != n - 1) puts("impossible");
    else cout << res << endl;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i <= n; i++) p[i] = i; //DSU init
    for (int i =  0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }

    kruskal();

    return 0;
}
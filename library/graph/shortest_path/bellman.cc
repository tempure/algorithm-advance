/*
Bellman-Ford求边数限制最短路
边可以为负 也可以有负权回路(边数限制问题)
时间复杂度 O(nm), n 表示点数，m 表示边数
*/
/*
从1号点到n号点的最多经过k条边的最短距离，
如果无法从1号点走到n号点，输出impossible
*/
const int N = 510, M = 10010;
int dist[N];
int n, m, k;
int backup[N];
//有边数限制 只能用bellman ford 算法，同时由于边数限制 负环也就无意义了
//bellman ford 算法迭代k次 求出的d数组 代表k条边能到达的最短路
struct Edge { //bellman 可直接用 struct来存边
    int a, b , w;
} edges[M];
int bellmanford() {
    dist[1] = 0;
    for (int i = 0; i < k; i++) { //迭代k次
        //记录上一次迭代的结果 防止迭代时发生边的串连
        memcpy(backup, dist, sizeof dist);
        for (int j = 0; j < m; j++) {
            int a = edges[j].a, b = edges[j].b, u = edges[j].w;
            dist[b] = min(dist[b], backup[a] + u);  //利用backup
        }
    }
    if (dist[n] > 0x3f3f3f3f / 2) return -1; //不能写成 dist[n] == 0x3f3f3f3f 即使不存在但是会被更新，不等于无穷了
    else return dist[n];
}
int main() {
    memset(dist, 0x3f, sizeof dist);
    cin >> n >> m >> k; //k是边数限制
    int x;
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }
    int t = bellmanford();
    if (t == -1) puts("impossible");
    else cout << t << endl;
    return 0;
}


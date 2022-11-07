/*
Kruskal时间复杂度O(mlogm), n 点数，m 边数
*/
const int N = 100010, M = 2 * N;
//kruskal直接结构体就可以了
int n, m;
int p[N];  //并查集父亲节点
struct Edge {
    int a, b, w;
    bool operator< (const Edge &u) const {
        return w < u.w;
    }
} edges[M];
int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}
int main() {
    cin >> n >> m;
    int a, b, x;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> x;
        edges[i] = {a, b , x};
    }
    sort(edges, edges + m);
    for (int i = 1; i <= n; i++) p[i] = i; //初始化并查集
    int res = 0, cnt = 0;  //res答案 cnt 记录当前加入的边数 最小生成树一共n - 1 条边
    for (int i = 0; i < m; i++) { //枚举所有的边
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        a = find(a), b = find(b);
        if (a != b) { //不连通 合并更新
            res += w;
            p[a] = b;
            cnt ++;
        }
    }
    if (cnt < n - 1) cout << "impossible" << endl;
    else cout << res << endl;
    return 0;
}
/*
例题:给定一棵N个节点的树，要求增加若干条边，把这棵树扩充为完全图，并满足图的唯一最小生成树仍然是这棵树。
求增加的边的权值总和最小是多少。
注意： 树中的所有边权均为整数，且新加的所有边权也必须为整数。
*/
//边权从小到大排序  然后kruskal 合并集合
//每次合并2个连通块时候 需要连接2个连通块内部所有的边 原来的树肯定至少有一条边已经连通这2个块
//假设原来树连通这2 块的最小边权是 w 那么新加的边权就是w + 1
//由于计算连通块内的点数 需要维护并查集的SIZE
const int N = 6010;  //有N-1条边
int n;
struct Edge {
    int a, b, w;
    bool operator< (const Edge & t) {
        return w < t.w;
    }
} e[N];
int p[N], sz[N];
int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}
int main() {
    int t;
    cin >> t;
    while (t --) {
        cin >> n;
        memset(p, 0, sizeof p);
        memset(sz, 0, sizeof sz);
        memset(e, 0, sizeof e);
        for (int i = 0; i < n - 1; i++) { //注意是输入n - 1条边
            int a, b, w;
            cin >> a >> b >> w;
            e[i] = {a, b, w};
        }
        sort(e, e + n);
        for (int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
        //因为是按照原来的存在的树的边排序的，所以每次遍历到的w就是原来树的边权值
        int res = 0;
        for (int i = 0; i < n; i++) {
            int a = find(e[i].a), b = find(e[i].b), w = e[i].w ;
            if (a != b) {
                res += (sz[a] * sz[b] - 1) * (w + 1); //减去一个已经存在的原来的树的边
                sz[b] += sz[a];
                p[a] = b;
            }
        }
        cout <<  res << endl;
    }
    return 0;
}
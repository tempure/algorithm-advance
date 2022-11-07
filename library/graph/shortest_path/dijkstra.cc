/*
朴素dijkstra算法
O(n^2+m), n 表示点数 m 表示边数
*/
const int N = 510, M = 100010;
int h[N], e[M], ne[M], w[M], d[N], idx;
bool v[N];  //是否被访问过 该节点
int n, m;
void dijkstra() {
    d[1] = 0;
    for (int i = 1; i < n; i++) {
        int x = 0;
        for (int j = 1; j <= n ; j++)
            if (!v[j] && (x == 0 || d[x] > d[j])) x = j;
        v[x] = 1;
        if (x == n) break; //对于只求第n个点的 此处可以优化，但是求所有点的单源最短路 就不需要了。
        for (int i = h[x]; ~i; i = ne[i]) {
            int y = e[i], u = w[i];
            if (d[y] > d[x] + u) d[y] = d[x] + u;
        }
    }
}
int main() {
    memset(h, -1 , sizeof h);
    memset(d, 0x3f , sizeof d);
    memset(v, 0, sizeof v);
    cin >> n >> m;
    int a, b, x;
    while (m--) {
        cin >> a >> b >> x;
        add(a, b, x);
    }
    dijkstra();
    if (d[n] == 0x3f3f3f3f) cout << -1 << endl;//路径不存在
    else cout << d[n] << endl;
    return 0;
}
/*
STL堆优化版dijkstra时间复杂度 O(mlogm), n 表示点数，m 表示边数
*/
typedef pair<int, int> pii;
const int N = 150010, M = 150010;
int h[N], e[M], ne[M], w[M], d[N], idx;
bool v[N];  //是否被访问过 该节点
int n, m;
//第一维度是dist  第二维是节点编号 pair默认按照第一维排序
priority_queue<pii , vector<pii>, greater<pii> > q;
void dijkstra() {
    d[1] = 0;
    q.push({0, 1});  //初始化第一个节点 距离为0
    while (q.size()) {
        int x = q.top().second; q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (int i = h[x]; i != -1; i = ne[i]) {
            int y = e[i], u = w[i];
            if (d[y] > d[x] + u) {
                d[y] = d[x] + u;
                q.push({d[y], y});
            }
        }
    }
}
/*
求单源次短路及其条数
*/
//先求最短路及路径数量 再求次短路 最后判断如果长度多1就加上
//d[i][0] 表示1到i的最短路径 cnt 同理
//d[i][1] 表示1到i的次短路径
//每个点的集合找到最短路和次短路 并且统计次数
const int N = 1010, M = 10010;
struct Ver {
    int ver, type, dist;//type记录是最短还是次短路
    bool operator> (const Ver &W) const {
        return dist > W.dist; // 大根堆 重载大于号
    }
};
int n, m, S, T;
int h[N], e[M], w[M], ne[M], idx;
int dist[N][2];
int cnt[N][2];
bool st[N][2];
void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}
int dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    dist[S][0] = 0; cnt[S][0] = 1;
    priority_queue<Ver, vector<Ver>, greater<Ver> > heap;
    heap.push({S, 0, 0});
    while (heap.size()) {
        Ver t = heap.top();
        heap.pop();
        int ver = t.ver, type = t.type, distance = t.dist, count = cnt[ver][type];
        if (st[ver][type]) continue;
        st[ver][type] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j  = e[i];
            if (dist[j][0] > distance + w[i]) {
                dist[j][1] = dist[j][0], cnt[j][1] = cnt[j][0]; //最小值沦为次小值
                heap.push({j, 1, dist[j][1]}); //次小值加入堆
                dist[j][0] = distance + w[i], cnt[j][0] = count;
                heap.push({j, 0, dist[j][0]}); //最小值加入堆
            }
            else if (dist[j][0] == distance + w[i]) cnt[j][0] += count;
            else if (dist[j][1] > distance + w[i]) {
                //比最小值小 比次小值大 更新次小值
                dist[j][1] = distance + w[i], cnt[j][1] = count;
                heap.push({j, 1, dist[j][1]});
            }
            else if (dist[j][1] == distance + w[i]) cnt[j][1] += count; //等于次小值
        }
    }
    int res = cnt[T][0];
    if (dist[T][0] + 1 == dist[T][1]) res += cnt[T][1];
    return res;
}
int main() {
    int t; cin >> t;
    while (t --) {
        scanf("%d%d", &n , &m);
        memset(h, -1 , sizeof h);
        idx = 0;
        while (m --) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
        }
        scanf("%d%d", &S, &T);
        printf("%d\n", dijkstra());
    }
    return 0;
}
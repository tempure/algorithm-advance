/*
spfa:平均情况下 O(m)，最坏情况下O(nm), n 点数，m 边数
给定一个n个点m条边的有向图，图中可能存在重边和自环，
边权可能为负数。求出1号点到n号点的最短距离
数据保证不存在负权回路。
*/
const int N = 100010, M = 100010;
int h[N], ne[M], idx, e[N], w[N], d[N];
bool v[N];
int n, m;
queue<int> q;
void spfa() {
    d[1] = 0; v[1] = 1;  //在队列中就是1 不在就是0
    q.push(1);
    while (q.size()) {
        int x = q.front(); q.pop();
        v[x] = 0;
        for (int i = h[x]; i != -1; i = ne[i]) {
            int y = e[i]; int u = w[i];
            if (d[x] + u < d[y]) {
                d[y] = d[x] + u;
                if (!v[y]) q.push(y), v[y] = 1;
            }
        }
    }
}
int main() {
    memset(h, -1, sizeof h);
    memset(v, 0, sizeof v);
    memset(d, 0x3f, sizeof d);
    cin >> n >> m;
    int a, b;
    int x;
    while (m --) {
        cin >> a >> b >> x;
        add(a, b, x);
    }
    spfa();
    if (d[n] == 0x3f3f3f3f) cout << "impossible"  << endl;
    else cout << d[n] << endl;
    return 0;
}

//spfa判负环
const int N = 2010, M = 10010;
int h[N], ne[M], idx, d[N], w[N], e[M];
bool v[N];
queue<int> q;
int cnt[N]; //cnt记录某个点到n号点的路径个数 不是路径长度
int n, m;
bool spfa() {
    //由于求整个图 而不是只求1号开始到其他点的路径否有负环，所以初始把所有点都加入队列
    for (int i = 1; i <= n; i++) q.push(i), v[i] = 1;
    while (q.size()) {
        int x = q.front(); q.pop();
        v[x] = 0;
        for (int i = h[x]; i != -1; i = ne[i]) {
            int y = e[i];
            if (d[y] > d[x] + w[i]) {
                d[y] = d[x] + w[i];
                cnt[y] = cnt[x] + 1; //更新路径之后 三角形不等式，然后边数加一
                if (cnt[y] >= n) return true; // n个点 无环路径最多 n - 1 条边 n条边更新了说明存在环，而且是负环 因为正环不可能更新
                if (!v[y]) q.push(y), v[y] = 1;
            }
        }
    }
    return false;
}
int main() {
    memset(h, -1, sizeof h);
    memset(v, 0, sizeof v);
    memset(d, 0x3f, sizeof d);
    int a, b , x;
    cin >> n >> m;
    while (m --) {
        cin >> a >> b >> x;
        add(a, b, x);
    }
    spfa();
    if (spfa()) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}


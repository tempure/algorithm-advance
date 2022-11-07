/*
时间复杂度 O(n+m)O(n+m), nn 表示点数，mm 表示边数
第一行包含两个整数n和m
接下来m行，每行包含两个整数x和y，表示存在一条从点x到点y的有向边(x, y)。
输出格式:共一行，如果存在拓扑序列，则输出任意一个合法的即可
否则输出-1。
*/
queue<int> q;
int n, m;
const int N = 100010;
int h[N], e[N], ne[N], idx;
int d[N], path[N];
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
bool topsort() {
    for (int i = 1; i <= n; i++)
        if (d[i] == 0) q.push(i);
    int cnt = 0;
    while (q.size()) {
        int t = q.front();
        path[cnt++] = t;
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (-- d[j] == 0) q.push(j);
        }
    }
    return cnt == n ;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    int a, b;
    while (m --) {
        cin >> a >> b;
        add(a, b);
        d[b]++;
    }
    if (topsort()) {
        for (int i = 0; i < n; i++) cout << path[i] << ' ';
        cout << endl;
    } else cout << -1 << endl;
    return 0;
}
/*
例题:可达性统计
给定一张N个点M条边的有向无环图，分别统计从每个点出发能够到达的点的数量。
输入格式
第一行两个整数N,M，接下来M行每行两个整数x,y，表示从x到y的一条有向边。
输出格式:输出共N行，表示每个点能够到达的点的数量。
*/
const int N = 30010;
int n, m;
int h[N], e[N], ne[N], idx;
int d[N], seq[N];
bitset<N> f[N];
void add(int a, int b) {
    e[idx] = b; ne[idx] = h[a], h[a] = idx++;
}
void topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!d[i]) q.push(i);
    int k = 0;
    while (q.size()) {
        int t = q.front();
        q.pop();
        seq[k ++] = t; //储存排序后的序列
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (-- d[j] == 0) q.push(j);
        }
    }
}
int main() {
    cin >> n >> m;
    memset(h , -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        d[b] ++;  // b点的入度加一
        add(a, b);
    }
    topsort();
    for (int i = n - 1; ~i; i--) { //从末尾开始
        int j = seq[i];  //拓扑序列的点 开始往后走
        f[j][j]  = 1; //自己可到达自己
        for (int p = h[j]; ~p; p = ne[p])
            f[j] |= f[e[p]];  //e[p] 代表这条边指向的点  求并集
    }
    for (int i = 1; i <= n; i++) cout << f[i].count() << endl;
}
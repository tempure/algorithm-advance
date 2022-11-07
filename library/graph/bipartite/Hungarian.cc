/*
匈牙利算法复杂度O(nm), n点数，m边数
求最大匹配数:
二分图，其中左半部包含n1个点（编号1~n1），右半部包含n2个点（编号1~n2），二分图共包含m条边。
数据保证任意一条边的两个端点都不可能在同一部分中。
求出二分图的最大匹配数。
*/
const int N = 510, M = 100010;
int n1, n2, m;
int h[N], ne[M], e[M], idx;
int match[N];  //右边的点 对应左边的匹配点是哪个
bool v[N];
//枚举左边的点 边的存储方向为左指向右边
//由于是二分图 所以左边部分点之间不可能有边，直接左右节点编号一样 混用无所谓 直接存就好
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
bool dfs(int x) { //只对左边的一个点进行的dfs操作
    for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if (!v[j]) { // 该右边的点还没有被左边该点匹配过
            v[j] = true;
            if (!match[j] || dfs(match[j])) { //j已经被占用
                //v[j] = true，则回溯过去的左边的点重选的时候不能选了
                //所以回溯过去原来的左边的点的只能在邻接表里面遍历下一个点
                match[j] = x;
                return true;
            }
        }
    }
    return false;
}
int main() {
    memset(h , -1 , sizeof h);
    cin >> n1 >> n2 >> m;
    int a, b;
    while (m --) {
        cin >> a >> b;
        add(a, b);
    }
    int res = 0;  //最终答案 最大匹配边数
    for (int i = 1; i <= n1; i++) { //枚举左边所有点
        memset(v, 0 , sizeof v); //每次枚举都清空右边的点来匹配
        if (dfs(i)) res++;
    }
    cout << res << endl;
    return 0;
}
/*
例题:关押罪犯
第一行为两个正整数N和M分别表示罪犯的数目以及存在仇恨的罪犯对数。
接下来的 M 行每行为三个正整数aj，bj，cj，表示aj号和bj号罪犯之间存在仇恨，其怨气值为cj。
数据保证1≤aj<bj<N,0<cj≤1000000000 且每对罪犯组合只出现一次。
*/
//二分图是 无向图的问题 但是有些有向图问题 本质还是 无向图
//二分边权 从冲突最大的开始 最终答案的取值范围为[0~1e9] 因为如果是二分图 那么就是0 如果是一个奇环 三个边都是1e9那么怎么分都是1e9
//所以每次二分mid 如果当前mid可以满足边权大于mid的点对都可以分开，也就是染色判定成功，那么就缩小mid
const int N = 20010, M = 200010; //无向边
int h[N], e[M], ne[M], w[M], idx;
int n, m;
int color[N]; //0 没有染色 1 白色 2 黑色
void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}
bool dfs(int u, int c, int mid) {
    color[u] = c;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (w[i] <= mid) continue;
        if (color[j]) {
            if (color[j] == c) return false;
        }
        else if (!dfs(j, 3 - c, mid)) return false;
    }
    return true;
}
bool check(int mid) {
    memset(color, 0, sizeof color);
    for (int i = 1; i <= n; i++)
        if (!color[i])
            if (!dfs(i, 1, mid)) return false;
    return true;
}
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }
    //二分
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", r);
    return 0;
}
/*
例题:骑士放置 最大独立集=点数-匹配数-禁止放置的点
给定一个 N*M 的棋盘，有一些格子禁止放棋子。
问棋盘上最多能放多少个不能互相攻击的骑士（国际象棋的“骑士”，类似于中国象棋的“马”，按照“日”字攻击，但没有中国象棋“别马腿”的规则）。
输入格式
第一行包含三个整数N,M,T，其中T表示禁止放置的格子的数量。
接下来T行每行包含两个整数x和y，表示位于第x行第y列的格子禁止放置，行列数从1开始。
输出格式
输出一个整数表示结果。
数据范围 1 <= N,M <= 100
*/
//如果2个点能互相 攻击到 那么就连一条边 那么最大独立集就是答案
//对于一般图 求最大独立集是NPC问题，但是这个图可以二染色，就是二分图，可以匈牙利多项式时间解出
//这里所说的二染色，是指每个点“日”字连接的点颜色是不一样的 而且横纵坐标之和奇偶性不同
#define x first
#define y second
const int N = 110;
int n, m, k;
pii match[N][N];
bool g[N][N], st[N][N];
int dx[8] = { -2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool dfs(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 1 || a > n || b < 1 || b > m) continue;
        if (g[a][b] || st[a][b]) continue;
        st[a][b] = true;
        pii t = match[a][b];
        if (t.x == 0 || dfs(t.x, t.y)) {
            match[a][b] = {x, y};
            return true;
        }
    }
    return false;
}
int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        g[x][y] = true; //不能放的格子
    }
    int res  = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if ((i + j) & 1 || g[i][j]) continue; //只需要单向匹配即可 就是枚举男的匹配女的
            memset(st, 0, sizeof st);
            if (dfs(i, j)) res ++;
        }
    cout << n * m - res - k  << endl;
    return 0;
}
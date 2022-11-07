/*
NIM博弈：给定n堆石子，两位玩家轮流操作，每次操作可以从任意一堆石子中拿走任意数量的石子（可以拿完，但不能不拿），最后无法进行操作的人视为失败。
*/
int n;
int main() {
    cin >> n; int x;
    ll res = 0;
    while (n--) {
        cin >> x;
        res ^= x;
    }
    if (res == 0) cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}
/*
台阶-NIM博弈
有一个n级台阶的楼梯，每级台阶上都有若干个石子，其中第i级台阶上有ai个石子(i>=1)。
两位玩家轮流操作，每次操作可以从任意一级台阶上拿若干个石子放到下一级台阶中（不能不拿）
已经拿到地面上的石子不能再拿，最后无法进行操作的人视为失败。
问如果两人都采用最优策略，先手是否必胜。
*/
int n;
int main() {
    cin >> n;
    int x;
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (i & 1) res ^= x;
    }
    if (res == 0) cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}
/*
集合NIM博弈:给定n堆石子以及一个由k个不同正整数构成的数字集合S,有两位玩家轮流操作，每次操作可以从任意一堆石子中拿取石子，每次拿取的石子数量必须包含于集合S，最后无法进行操作的人视为失败。问如果两人都采用最优策略，先手是否必胜。
*/
const int N = 110, M = 10010;
//每一堆石子都可以看为一个有向图，然后求初始节点的SG函数 每一个节点的出边对应能取的所有状态
int n, m;
int s[N], f[M];  //s表示集合的元素 ，f 是sg函数值
int sg(int x) {
    if (f[x] != -1) return f[x];
    unordered_set<int> S;
    for (int i = 0; i < m; i++) {
        int sum = s[i];
        if (x >= sum) S.insert(sg(x - sum));
    }
    for (int i = 0; ; i++) {
        if (!S.count(i)) return f[x] = i;
    }
}
int main() {
    cin >> m;
    for (int i = 0; i < m; i++) cin >> s[i];
    cin >> n;
    memset(f, -1, sizeof f);
    int res = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        res ^= sg(x);//求出所有有向图的sg函数然后全部异或
    }
    if (res == 0) cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}
/*
拆分NIM博弈:给定n堆石子，两位玩家轮流操作，每次操作可以取走其中的一堆石子，然后放入两堆规模更小的石子（新堆规模可以为0，且两个新堆的石子总数可以大于取走的那堆石子数），最后无法进行操作的人视为失败。
问如果两人都采用最优策略，先手是否必胜。
*/
//石子堆的最大值在减小 所以博弈一定会结束
//每堆石子看坐有向图 然后全部求SG函数
const int N = 110;
int f[N];
int sg(int x) {
    if (f[x] != -1) return f[x];
    unordered_set<int> S;
    //枚举可以到达的状态
    for (int i = 0; i < x; i++) //第一堆
        for (int j = 0; j <= i; j++) //第二堆
            S.insert(sg(i) ^ sg(j));
    //mex 函数
    for (int i = 0;; i++)
        if (!S.count(i))
            return f[x] = i;

}
int main() {
    int n; cin >> n;
    int res = 0;
    memset(f, -1, sizeof f);
    while (n --) {
        int x;
        cin >> x;
        res ^= sg(x);
    }
    if (res == 0) cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}
/*
有向图博弈:给定一个有 N 个节点的有向无环图，图中某些节点上有棋子，两名玩家交替移动棋子。
玩家每一步可将任意一颗棋子沿一条有向边移动到另一个点，无法移动者输掉游戏。
对于给定的图和棋子初始位置，双方都会采取最优的行动，询问先手必胜还是先手必败。
输入格式
第一行，三个整数 N,M,K，N 表示图中节点总数，M 表示图中边的条数，K 表示棋子的个数。
接下来 M 行，每行两个整数 X,Y 表示有一条边从点 X 出发指向点 Y。
接下来一行， K 个空格间隔的整数，表示初始时，棋子所在的节点编号。
节点编号从 1 到 N。
输出格式:若先手胜，输出 win，否则输出 lose
*/
const int N = 2010, M = 6010;
int n, m, k;
int h[N], e[M], ne[M], idx;
int sg[N];
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
int SG(int u) {
    if (sg[u] != -1) return sg[u];
    set<int> s;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        s.insert(SG(j));
    }
    for (int i = 0; ; i++)
        if (!s.count(i)) {
            sg[u] = i;
            break;
        }
    return sg[u];
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    memset(h, -1, sizeof h);
    memset(sg, -1, sizeof sg);
    for (int i = 0; i < m; i++) {
        int a, b ;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    int res = 0;
    for (int i = 0; i < k; i++) {
        int u; scanf("%d", &u);
        res ^= SG(u);
    }
    if (res) puts("win");
    else puts("lose");
    return 0;
}
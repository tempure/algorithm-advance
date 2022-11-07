/*给定一个N*M的数字矩阵，矩阵中的元素属于{0,1}。找到一个行的集合,这些行每一列都包含数字1，并且行数尽可能少。第一行输出最少行数。第二行输出行的编号（行编号1~N）。如果方案不唯一，则以任意顺序输出任意方案
和精确覆盖区别在于每次删除一列的时候，不会删除该列有1的位置的所有的行,因为这些行可以被多次选择
由于删除比较少，剪枝较差，所以需要用迭代加深的思路来优化
启发函数是“遍历所有列，每次对于当前列，选当前列所有有1的行，直到所有列被覆盖但是选择的行数只增加1”
启发函数的值肯定是要<=真实值的，假设需要选5行才能真正覆盖所有的列，但是启发式函数可能只选了3行
假设当前的IDA*搜索最大层数(选择的行数)为depth,当前层数为dep_current,那么对于不等式 h()+dep_current >depth 意味着当前最大depth的IDA*算法不能搜出答案，需要扩大depth*/
const int N = 10010; //最多所有位置都是1
int n, m;
int l[N], r[N], u[N], d[N], col[N], row[N], s[N], idx;
int ans[N];
bool st[110];  //启发函数标记该列是否被选
void init() {
    for (int i = 0; i <= m; i++) {
        l[i] = i - 1, r[i] = i + 1;
        col[i] = u[i] = d[i] = i;
        s[i] = 0;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}
void add(int &hh, int&tt, int x, int y) { //上下左右都是头插
    row[idx] = x, col[idx] = y, s[y] ++;
    u[idx] = y, d[idx] =  d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx ++;
}
int h() { //启发函数 返回当前最少需要的行数(才可以找到答案)
    int cnt = 0; //选择的行数
    memset(st, 0, sizeof st);
    for (int i = r[0]; i; i = r[i]) { //遍历还没有被覆盖的列
        if (st[col[i]]) continue; //当前列被选过就直接跳过
        cnt ++;
        st[col[i]] = true;
        for (int j = d[i]; j != i; j = d[j])
            for (int k = r[j]; k != j; k = r[k])
                st[col[k]] = true;
    }
    return cnt;
}
void remove(int p) {//删第p列但不删该列有1的行也不删表头
    for (int i = d[p]; i != p; i = d[i]) {
        r[l[i]] = r[i];
        l[r[i]] = l[i];
    }
}
void resume(int p) {
    for (int i = u[p]; i != p; i = u[i]) {
        r[l[i]] = i;
        l[r[i]] = i;
    }
}
bool dfs(int k, int depth) { //k当前搜索的层数 depth当前IDA*最大的搜索层数
    if (k + h() > depth) return false;
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[p] > s[i])
            p = i; //找出1最少的列
    for (int i = d[p]; i != p; i = d[i]) {
        ans[k] = row[i];
        remove(i); //注意此处的删除恢复位置和精确覆盖不一样
        for (int j = r[i]; j != i; j = r[j]) remove(j);
        if (dfs(k + 1, depth)) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(j);
        resume(i);
    }
    return false;
}
int main() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= n; i++) {
        int hh = idx, tt = idx;
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            if (x) add(hh, tt, i, j);
        }
    }
    int depth = 0; //当前IDA*搜索的最大层数
    while (!dfs(0, depth)) depth++; //没有搜到就增大depth
    cout << depth << endl;
    for (int i = 0; i < depth; i++) cout << ans[i] << ' ';
    return 0;
}
/*HDU2295《雷达》:N个城市需要被雷达覆盖。有M个雷达站，但只有K个操作员，因此最多只能操作 K 个雷达。雷达的覆盖区域为以自身为圆点的圆形区域，所有雷达的覆盖半径都等于R。使用不超过K个雷达的情况下所有城市都被雷达覆盖求R最小值。
输入格式:第一行包含整数 T，表示共有 T 组测试数据。每组数据第一行包含三个整数 N,M,K。接下来 N 行，每行包含两个整数 X,Y，表示一个城市的坐标。再接下来 M 行，每行包含两个整数 X,Y，表示一个雷达的坐标。
输出格式:每组数据输出一个实数作为结果，结果保留六位小数。
数据范围:1<=T<=20,1<=N,M<=50,1<=K<=M,0<=X,Y<=1000*/
#define x first
#define y second
typedef pair<double, double> pdd;
const int N = 55, M = N * N; //M是点数上界
int n, m, k;
int l[M], r[M], u[M], d[M], row[M], col[M], s[M], idx;
bool st[N];
pdd city[N], station[N]; //城市和雷达站
/*二分半径，求出当前半径选多少个雷达站即可覆盖所有城市，如果当前半径下求出的雷达站数量>=k
那就减小半径，直到二分最后的答案即可。
每次二分，用雷达站作为DLX的行，城市作为列，枚举每个雷达站，如果和城市的距离<=当前半径，那就连边即可。*/
void init() {
    for (int i = 0; i <= n; i++) {
        l[i] = i - 1, r[i] = i + 1;
        col[i] = u[i] = d[i] = i;
        s[i] = 0;
    }
    l[0] = n, r[n] = 0;
    idx = n + 1;
}
void add(int &hh, int &tt, int x, int y) {
    row[idx] = x, col[idx] = y, s[y] ++;
    u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx ++;
}
int h() {
    int res = 0;
    memset(st, 0, sizeof st);
    for (int i = r[0]; i; i = r[i]) {
        if (st[i]) continue;
        res ++;
        st[i] = true;
        for (int j = d[i]; j != i; j = d[j])
            for (int k = r[j]; k != j; k = r[k])
                st[col[k]] = true;
    }
    return res;
}
void remove(int p) {
    for (int i = d[p]; i != p; i = d[i]) {
        r[l[i]] = r[i];
        l[r[i]] = l[i];
    }
}
void resume(int p) {
    for (int i = u[p]; i != p; i = u[i]) {
        r[l[i]] = i;
        l[r[i]] = i;
    }
}
bool dfs(int k, int depth) {
    if (k + h() > depth) return false;
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[p] > s[i])
            p = i;
    for (int i = d[p]; i != p; i = d[i]) {
        remove(i);
        for (int j = r[i]; j != i; j = r[j]) remove(j);
        if (dfs(k + 1, depth)) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(j);
        resume(i);
    }
    return false;
}
bool check(pdd a, pdd b, double mid) { //城市和雷达站距离是否小于等于mid
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy <= mid * mid;
}
bool check(double mid) { //二分当前dlx
    init(); //每次二分都要初始化
    for (int i = 1; i <= m; i++) {
        int hh = idx, tt = idx;
        for (int j = 1; j <= n; j++)
            if (check(station[i], city[j], mid))
                add(hh, tt, i, j);
    }
    int depth = 0;
    while (depth <= k && !dfs(0, depth)) depth++;
    return depth <= k;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++) scanf("%lf%lf", &city[i].x, &city[i].y);
        for (int i = 1; i <= m; i++) scanf("%lf%lf", &station[i].x, &station[i].y);
        double l = 0, r = 1600; //r是最大的距离为1000*sqrt(2)
        while (r - l > 1e-10) {
            double mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid;
        }
        printf("%lf\n", r);
    }
    return 0;
}
/*线段树套multiset
维护一个长度为 n 的序列，提供以下操作：
1 pos x，将 pos 位置的数修改为 x。
2 l r x，查询整数 x 在区间 [l,r] 内的前驱(前驱定义为小于 x，且最大的数)。
数列中的位置从左到右依次标号为 1~n。保证一定有解。
区间 [l,r] 表示从位置 l 到位置 r 之间（包括两端点）的所有数字。
区间内排名为 k 的值指区间内从小到大排在第 k 位的数值。（位次从 1 开始）*/
const int N = 50010, M = N * 4, INF = 1e9; //线段树开4倍的点
int n, m;
struct Tree {
    int l, r;
    multiset<int> s;
} tr[M];
int w[M]; //存储初始元素用来建树
void build(int u, int l, int r) { //u是当前区间的编号 也就是节点的编号
    tr[u] = {l, r};
    tr[u].s.insert(-INF), tr[u].s.insert(INF); //避免找不到
    for (int i = l; i <= r; i++)  tr[u].s.insert(w[i]);
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
void change(int u, int p, int x) { //修改是先删旧的再插新的
    tr[u].s.erase(tr[u].s.find(w[p]));  //find只找到第一个删掉 不是全部删除
    tr[u].s.insert(x);
    if (tr[u].l == tr[u].r) return;
    int mid = tr[u].l + tr[u].r >> 1;
    if (p <= mid) change(u << 1, p, x);
    else change(u << 1 | 1, p, x);
}
int query(int u, int a, int b, int x) {
    if (tr[u].l >= a && tr[u].r <= b) {
        auto it = tr[u].s.lower_bound(x);
        -- it;
        return *it;
    }
    int mid = tr[u].l + tr[u].r >> 1,  res = -INF;
    if (a <= mid) res = max(res, query(u << 1, a, b, x));
    if (b > mid) res = max(res, query(u << 1 | 1, a, b, x));
    return res;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    build(1, 1, n); //1是root区间 也就是最大的区间
    while (m --) {
        int op, a, b, x;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &a, &x);
            change(1, a, x);
            w[a] = x;
        }
        else {
            scanf("%d%d%d", &a, &b, &x);
            printf("%d\n", query(1, a, b, x));
        }
    }
    return 0;
}
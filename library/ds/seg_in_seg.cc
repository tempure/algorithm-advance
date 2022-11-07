/*ZJOI2013《K大数查询》
有 N 个位置，M 个操作。每个位置可以同时存储多个数。
操作有两种，每个位置当作一个集合
1 a b c，表示在第a个位置到第b个位置，每个位置加入一个数c。
2 a b c，表示询问从第a个位置到第b个位置，第c大的数是多少。
1<=N,M<=50000,1<=a<=b<=N,
1 操作中的 c 的绝对值不超过 N,
2 操作中 c 满足 1<=c<=2^31−1。*/
/*主席树求区间kth是离线做法，树套树为动态求区间kth。
权值线段树：就是以(离散化)权值为下标建立线段树
此题为权值线段树套区间线段树模板题，动态开点，只有外层单点加，所以不用pushup/pushdown，直接标记永久化*/
const int N = 50010, P = N * 17 * 17, M = N * 4;
int n, m;
struct Tree {
    int l, r, sum, add;
} tr[P];
int L[M], R[M], T[M], idx;
struct Query {
    int op, a, b, c;
} q[N];
vector<int> nums; //离散化
int get(int x) {
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}
void build(int u, int l, int r) {
    L[u] = l, R[u] = r, T[u] = ++ idx;
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
int intersection(int a, int b, int c, int d) {
    return min(b, d) - max(a, c) + 1;
}
void update(int u, int l, int r, int pl, int pr) {
    tr[u].sum += intersection(l, r, pl, pr);
    if (l >= pl && r <= pr) {
        tr[u].add ++ ;
        return;
    }
    int mid = l + r >> 1;
    if (pl <= mid) {
        if (!tr[u].l) tr[u].l = ++ idx;
        update(tr[u].l, l, mid, pl, pr);
    }
    if (pr > mid) {
        if (!tr[u].r) tr[u].r = ++ idx;
        update(tr[u].r, mid + 1, r, pl, pr);
    }
}
void change(int u, int a, int b, int c) {
    update(T[u], 1, n, a, b);
    if (L[u] == R[u]) return;
    int mid = L[u] + R[u] >> 1;
    if (c <= mid) change(u << 1, a, b, c);
    else change(u << 1 | 1, a, b, c);
}
int get_sum(int u, int l, int r, int pl, int pr, int add) {
    if (l >= pl && r <= pr) return tr[u].sum + (r - l + 1) * add;
    int mid = l + r >> 1, res = 0;
    add += tr[u].add;
    if (pl <= mid) {
        if (tr[u].l) res += get_sum(tr[u].l, l, mid, pl, pr, add);
        else res += intersection(l, mid, pl, pr) * add;
    }
    if (pr > mid) {
        if (tr[u].r) res += get_sum(tr[u].r, mid + 1, r, pl, pr, add);
        else res += intersection(mid + 1, r, pl, pr) * add;
    }
    return res;
}
int query(int u, int a, int b, int c) {
    if (L[u] == R[u]) return R[u];
    int mid = L[u] + R[u] >> 1;
    int k = get_sum(T[u << 1 | 1], 1, n, a, b, 0);
    if (k >= c) return query(u << 1 | 1, a, b, c);
    return query(u << 1, a, b, c - k);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i ++ ) {
        scanf("%d%d%d%d", &q[i].op, &q[i].a, &q[i].b, &q[i].c);
        if (q[i].op == 1) nums.push_back(q[i].c);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    build(1, 0, nums.size() - 1);
    for (int i = 0; i < m; i ++ ) {
        int op = q[i].op, a = q[i].a, b = q[i].b, c = q[i].c;
        if (op == 1) change(1, a, b, get(c));
        else printf("%d\n", nums[query(1, a, b, c)]);
    }
    return 0;
}
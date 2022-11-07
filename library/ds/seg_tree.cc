/*
支持的操作：
单点修改/查询区间最大元素/区间GCD
区间求和/区间最大连续子段和/区间修改
*/
/*
区间修改，区间查询模板
1、“C l r d”，表示把 A[l],A[l+1],…,A[r] 都加上 d。
2、“Q l r”，表示询问 数列中第 l~r 个数的和。
*/
const int N = 100010;
int n, m;
int w[N];
struct Node {
    int l, r;
    ll sum, add;
} tr[N * 4];
void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}
void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) {
        left.add += root.add, left.sum += 1ll * (left.r - left.l + 1) * root.add;
        right.add += root.add, right.sum += 1ll * (right.r - right.l + 1) * root.add;
        root.add = 0;
    }
}
void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += 1ll * (tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
    }
    else {
        pushdown(u); //需要分裂 然后递归给子节点打tag
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}
ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll sum = 0;
    if (l <= mid) sum = query(u << 1, l, r);
    if (r > mid) sum += query(u << 1 | 1, l, r);
    return sum;
}
void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, w[r], 0};
    else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    build(1, 1, n);
    char op[2];
    int l, r, d;
    while (m --) {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C') {
            scanf("%d", &d);
            modify(1, l, r, d);
        }
        else printf("%lld\n", query(1, l, r));
    }
    return 0;
}
/*
区间最大连续子段和/单点修改
1、“1 x y”，查询区间 [x,y] 中的最大连续子段和
2、“2 x y”，把 A[x] 改成 y。
*/
//记录左子节点的最大后缀和 和 右边子节点的最大前缀和
//那么父节点的最大子段和就是max{左子节点最大子段和, 右子节点最大子段和 , 左子节点最大后缀+右子节点最大前缀
//这个过程是递归的 回溯的时候 子节点只会pushup自己段的最大前后缀给父节点
const int N = 5e5 + 10;
int n, m;
int w[N]; //序列
struct Node {
    int l, r;
    int sum; //当前段的区间和
    int lmax, rmax; //子节点最大前后缀
    int tmax; //当前段的最大子段和
} tr[N * 4];
void pushup(Node &u, Node &l, Node & r) {
    u.sum = l.sum + r.sum;
    u.lmax = max(l.lmax, l.sum + r.lmax); //维护
    u.rmax = max(r.rmax, r.sum + l.rmax);
    u.tmax = max(max(l.tmax, r.tmax), l.rmax + r.lmax);
}
void pushup(int u) {
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
void build(int u, int l, int r) {
    tr[u].l = l, tr[u].r = r;
    if (l == r) tr[u] = {l, r, w[r], w[r], w[r], w[r]};
    else {
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
int modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) tr[u] = {x, x, v, v, v, v};
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}
Node query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) return query(u << 1, l, r);
        else if (l > mid) return query(u << 1 | 1, l , r);
        else {
            auto left = query(u << 1, l , r);
            auto right = query(u << 1 | 1, l, r);
            Node res;
            pushup(res, left, right);
            return res;
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    build(1, 1, n);
    int k, x, y;
    while (m --) {
        scanf("%d%d%d", &k, &x, &y);
        if (k == 1) {
            if (x > y) swap(x, y);
            printf("%d\n", query(1, x, y).tmax);
        }
        else modify(1, x, y);
    }
    return 0;
}
/*
单点修改/区间最大数
1添加操作：向序列后添加一个数，序列长度变成 n+1；
2询问操作：询问这个序列中最后 L 个数中最大的数是多少。
*/
const int N = 200010;
int m, p;
struct Node {
    int l, r ;
    int v; //区间[l,r] 的最大值
} tr[N * 4];
//子节点更新父节点
void pushup(int u) {
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}
int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v; //查询的区间完全包含在树中的某个段区间内 段的最大值就是候选值
    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r); // 左边 有交集 递归向下查左边 注意l <= mid
    if (r > mid) v = max(v, query(u << 1 | 1, l , r)); //右边有交集 递归查右边
    return v;
}
void modify(int u, int x, int v) { //将x位置的点的值修改为v
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v; //叶节点找到了直接修改
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x , v);
        else modify(u << 1 | 1, x, v);
        pushup(u); //修改之后要更新最大值 回溯的时候
    }
}
void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return ;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
int main() {
    int n = 0, last = 0; //上一次查询的结果
    scanf("%d%d", &m, &p);
    build(1, 1, m);
    char op[2];
    int x;
    int l;
    while (m --) {
        scanf("%s%d", op, &x);
        //如果是 A t，则表示向序列后面加一个数，加入的数是 (t+a) mod p。其中，t 是输入的参数，
        //a 是在这个添加操作之前最后一个询问操作的答案（如果之前没有询问操作，则 a=0）。
        if (*op == 'Q') {
            last = query(1, n - x + 1, n);
            printf("%d\n", last);
        }
        else { //修改操作 由题意而定
            modify(1, n + 1, (last + x) % p);
            n ++;
        }
    }
    return 0;
}
/*
例题:维护序列
把数列中的一段数全部乘一个值；
把数列中的一段数全部加一个值；
询问数列中的一段数的和，结果模p。
操作 1：1 t g c，表示把所有满足 t≤i≤g 的 ai 改为 ai×c；
操作 2：2 t g c，表示把所有满足 t≤i≤g 的 ai 改为 ai+c；
操作 3：3 t g，询问所有满足 t≤i≤g 的 ai 的和 模 P 的值。
*/
//全部使用先乘再加的操作顺序 这样可以维护计算的表达式一致性
//x * a + b) * c +  d) * e + f
//开2个lazy tag 记录每次乘或者加即可
//加法lazytag：与正常的线段树一样
//乘法lazytag：将原先的加法glazytag乘上需要乘的数，
//再将乘法lazytag乘上需要乘的数。下发lazytag时先下发乘法标记
const int N = 100010;
int n, p, m;
int w[N];
struct Node {
    int l, r;
    int sum, add, mul;
} tr[N * 4];
void pushup(int u) {
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % p;
}
void eval(Node &t, int add, int mul) {
    t.sum = ((ll)t.sum * mul + (ll)(t.r - t.l + 1) * add) % p;
    t.mul = (ll)t.mul * mul % p;
    t.add = ((ll)t.add * mul + add) % p;
}
void pushdown(int u) {
    eval(tr[u << 1], tr[u].add, tr[u].mul);
    eval(tr[u << 1 | 1], tr[u].add, tr[u].mul);
    tr[u].add = 0,  tr[u].mul = 1;
}
void modify(int u, int l, int r, int add, int mul) {
    if (tr[u].l >= l && tr[u].r <= r) eval(tr[u], add, mul);
    else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, add, mul);
        if (r > mid) modify(u << 1 | 1, l, r, add , mul);
        pushup(u);
    }
}
ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll sum = 0;
    if (l <= mid) sum = query(u << 1, l, r) % p;
    if (r > mid) sum = (sum + query(u << 1 | 1, l , r)) % p;
    return sum;
}
void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, w[r], 0, 1}; //加0 乘1
    else {
        tr[u] = {l, r, 0, 0, 1};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
int main() {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    build(1, 1, n);
    scanf("%d", &m);
    while (m --) {
        int t, l, r, d;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1) {
            scanf("%d", &d);
            modify(1, l, r, 0, d);
        }
        else if (t == 2) {
            scanf("%d", &d);
            modify(1, l, r, d, 1);
        }
        else printf("%d\n", query(1, l, r));
    }
    return 0;
}
/*
区间修改/区间最大GCD
1、“C l r d”，表示把 A[l],A[l+1],…,A[r] 都加上 d。
2、“Q l r”，表示询问 A[l],A[l+1],…,A[r] 的最大公约数(GCD)
*/
//gcd(a,b) = gcd(a, b-a) 差分
const int N = 500010;
int n, m;
ll w[N];
struct Node {
    int l, r;
    ll sum, d; //差分数组的区间和 以及gcd
} tr[N * 4];
void pushup(Node &u, Node &l, Node &r) {
    u.sum = l.sum + r.sum;
    u.d = gcd(l.d, r.d);
}
void pushup(int u) {
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
void build(int u, int l, int r) {
    ll b = w[r] - w[r - 1]; //建立差分数组
    if (l == r) tr[u] = {l, r, b, b};
    else {
        tr[u].l = l, tr[u].r = r;
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
void modify(int u, int x, ll v) {
    if (tr[u].l == x && tr[u].r == x) {
        ll b = tr[u].sum + v;
        tr[u] = {x, x, b, b};
    }
    else {
        int mid = tr[u].l + tr[u].r >>  1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}
Node query(int u, int l, int r) {
    if (l > r) return {0};
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) return query(u << 1, l, r);
        else if (l > mid) return query(u << 1 | 1, l, r);
        else {
            auto left = query(u << 1, l,  r);
            auto right = query(u << 1 | 1, l , r);
            Node res;
            pushup(res, left, right);
            return res;
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &w[i]);
    build(1, 1, n);
    int l, r;
    ll d;
    char op[2];
    while (m --) {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'Q') {
            auto left = query(1, 1, l);
            Node right({0, 0, 0, 0});
            if (l + 1 <= r) right = query(1, l + 1, r);
            printf("%lld\n", abs(gcd(left.sum, right.d)));
        }
        else {
            scanf("%lld", &d);
            modify(1, l , d);
            if (r + 1 <= n)  modify(1, r + 1, -d);
        }
    }
    return 0;
}

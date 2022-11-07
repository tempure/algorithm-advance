#include <iostream>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
int n, m;
int a[N];

struct Node {
    int l, r, add;
    ll sum;
} tr[N * 4];

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u) {
    auto &root = tr[u];
    auto &left = tr[u << 1], &right = tr[u << 1 | 1];
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
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}


ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);

    ll sum = 0;
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) sum += query(u << 1, l, r);
    if (r > mid) sum += query(u << 1 | 1, l, r);
    return sum;
}

void build(int u, int l, int r) {
    if (l == r)tr[u] = {l, r, 0, a[r]};
    else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    //  for(int i = 1; i <= n * 4; i++) cout << tr[i].sum << ' ';
    //  cout << endl;
    while (m --) {
        char op;
        int l, r;
        int d;
        cin >> op >> l >> r;
        if (op == 'C') {
            cin >> d;
            modify(1, l, r, d);
        }
        else cout << query(1, l, r) << endl;
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
// using ll = long long;
#define int long long
const int N = 2e5 + 10;
int m, p;

//2021 10.7 update:
//此题数据被加强，取模那里相加 a + last 可能会爆掉 int

struct Node {
    int l, r;
    int v; //after l and r give v value, default init value is 0
} tr[N * 4];

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void pushup(int u) {
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r);
    if (r > mid) v = max(v, query(u << 1 | 1, l, r));
    return v;
}

void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v;
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

void solve() {
    int n = 0, last = 0;
    cin >> m >> p;

    build(1, 1, m); //最多加m次，也就是tr[]长度最长是m
    char op[2];
    int x;
    int l;
    while (m --) {
        scanf("%s%d", op, &x);
        if (*op == 'Q') {
            last = query(1, n - x + 1, n);
            printf("%d\n", last);
        }
        else {
            modify(1, n + 1, (last + x) % p);
            n ++;
        }
    }
}

signed main() {
    solve();
    return 0;
}
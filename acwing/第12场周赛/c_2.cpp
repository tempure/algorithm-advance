//https://codeforces.com/problemset/problem/52/C

//lazy tag 线段树模板题

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;
const ll INF = 1e18;

int n, m;
int w[N];

struct Node {
    int l, r;
    ll dt, mn; //修改的lazg tag, 以及当前区间min
} tr[N * 4];

void pushup(int u) {
    tr[u].mn = min(tr[u << 1 | 1].mn, tr[u << 1].mn);
}

void pushdown(int u) {
    auto &root = tr[u], &l = tr[u << 1], &r = tr[u << 1 | 1];
    l.dt += root.dt, l.mn += root.dt;
    r.dt += root.dt, r.mn += root.dt;
    root.dt = 0;
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, 0, w[l]};
    else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

//add operation
void update(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].dt += d, tr[u].mn += d;
    }
    else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) update(u << 1, l, r, d);
        if (r > mid) update(u << 1 | 1, l, r, d);
        pushup(u);
    }
}

ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].mn;
    }
    else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        ll res = INF;
        if (l <= mid) res = query(u << 1, l, r);
        if (r > mid) res = min(res, query(u << 1 | 1, l, r));
        return res;
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> w[i];
    build(1, 0, n - 1);
    cin >> m;
    while (m --) {
        int l, r, d;
        char c;
        scanf("%d %d%c", &l, &r, &c); //cin ignore space
        if (c == '\n') {
            if (l <= r) cout << query(1, l, r) << endl;
            else cout << min(query(1, l, n - 1), query(1, 0, r)) << endl;
        }
        else {
            cin >> d;
            if (l <= r) update(1, l, r, d);
            else update(1, l, n - 1, d), update(1, 0, r, d);
        }
    }
}

int main() {
    solve();
    return 0;
}
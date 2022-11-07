#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
#define x first
#define y second

const int N = 5010;

int n, m;
pll a[N], b[N];
int ans[N];

ll cross(ll x1, ll y1, ll x2, ll y2) {
    return x1 * y2 - x2 * y1;
}

ll area(pll a, pll b, pll c) {
    return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

int find(ll x, ll y) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + r >> 1;
        if (area(b[mid], a[mid], {x, y}) > 0) r = mid;
        else l = mid + 1;
    }
    return r;
}

void solve() {
    bool is_first = true;
    while (cin >> n && n) {
        ll x1, y1, x2, y2;
        cin >> m >> x1 >> y1 >> x2 >> y2;
        for (int i = 0; i < n; i++) {
            ll u, l;
            cin >> u >> l;
            a[i] = {u, y1}, b[i] = {l, y2};
        }
        a[n] = {x2, y1}, b[n] = {x2, y2};

        if (is_first) is_first = false;
        else puts("");

        memset(ans, 0, sizeof ans);
        while (m--) {
            ll x, y;
            cin >> x >> y;
            ans[find(x, y)] ++;
        }
        for (int i = 0; i <= n; i++)
            printf("%d: %d\n", i, ans[i]);
    }
}

int main() {
    solve();
    return 0;
}
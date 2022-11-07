#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
using ll = long long;
using pll = pair<ll, ll>;

/*
一个二分注意的细节：所有挡板的编号是从0开始的，每个挡板的编号代表这个挡板左边的区域, a[n]是最右边的边界，自己要加上去
这个右边边界也可以是算作一个挡板,也就是n号挡板，最左边的边界直接忽略掉，不影响二分的结果
*/

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
    bool first = true;
    while (cin >> n && n) {
        ll x1, y1, x2, y2;
        cin >> m >> x1 >> y1 >> x2 >> y2;
        for (int i = 0; i < n; i++) { //注意此处挡板的编号是从0开始的
            ll u, l;
            cin >> u >> l;
            a[i] = {u, y1}, b[i] = {l, y2};
        }
        a[n] = {x2, y1}, b[n] = {x2, y2};

        if (first) first = false;
        else puts("");

        memset(ans, 0, sizeof ans);
        while (m --) {
            ll x, y;
            cin >> x >> y;
            ans[find(x, y)] ++;
        }
        for (int i = 0; i <= n; i++) printf("%d: %d\n", i, ans[i]);
    }
}

int main() {
    solve();
    return 0;
}
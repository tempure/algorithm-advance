#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

//扫描线
//以y轴方向开线段树 不需要pushdown操作(即使有不影响 但是代码边长) 只需要每次查根即可

const int N = 100010;
int n;
struct Segment {
    double x, y1, y2;
    int k;
    bool operator< (const Segment & t) const {
        return x < t.x;
    }
} seg[N * 2];

struct Node {
    int l, r;
    int cnt;
    double len;
} tr[N * 8];

vector<double> ys;

int find(double y) {
    return lower_bound(all(ys), y) - ys.begin();
}

void pushup(int u) {
    if (tr[u].cnt) tr[u].len = (ys[tr[u].r + 1] - ys[tr[u].l]);
    else if (tr[u].l != tr[u].r) {
        tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    }
    else tr[u].len = 0;
}

void modify(int u, int l, int r, int k) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].cnt += k;
        pushup(u);
    }
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, k);
        if (r > mid) modify(u << 1 | 1, l, r, k);
        pushup(u);
    }
}


void build(int u, int l, int r) {
    tr[u] = {l, r, 0, 0};
    if (l != r) {
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
}

int main() {
    int T = 1;
    while (scanf("%d", &n), n) {
        ys.clear();
        for (int i = 0, j = 0; i < n; i++) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[j++] = {x1, y1, y2, 1};
            seg[j++] = {x2, y1, y2, -1};
            ys.push_back(y1),  ys.push_back(y2);
        }
        sort(all(ys));
        ys.erase(unique(all(ys)), ys.end());

        build(1, 0, ys.size() - 2); //区间的个数比点的个数少一个

        sort(seg, seg + n * 2);

        double res = 0;
        for (int i = 0; i < n * 2; i ++) {
            if (i > 0) res += tr[1].len * (seg[i].x - seg[i - 1].x);
            modify(1, find(seg[i].y1), find(seg[i].y2) - 1, seg[i].k);
        }

        printf("Test case #%d\n", T++);
        printf("Total explored area: %.2lf\n\n", res);
    }

    return 0;
}
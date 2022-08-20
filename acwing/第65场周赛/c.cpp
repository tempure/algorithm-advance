#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define endl '\n'
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
//head

//四个点可以确定此凸多边形的外接矩形，每个边占一个点，此时曼哈顿距离最大，就是外接矩形的周长
//所以只需要考虑3个点的情况即可
//三个点就是一个三角形，对于此三角形的外接矩形，肯定有一个点位于矩形的四个拐角之一
//所以对于3个点只需考虑每个点是当前外接矩形的左下角顶点，左上角，右上角，右下角顶点，然后取max即可
//对于左下角举例，那么另外两个点就取纵坐标最大的，和横坐标最大的，其余三种情况同理

const int N = 3e5 + 10, INF = 0x3f3f3f3f;
int n;
int x[N], y[N];

void solve() {
    cin >> n;
    int u = -INF, d = INF, l = INF, r = -INF; //上下左右边界
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        u = max(u, y[i]), d = min(d, y[i]);
        l = min(l, x[i]), r =  max(r, x[i]);
    }
    int res = 0;
    for (int i = 0; i < n; i++)
        //三角形四种拐角的情况
        res = max(res, max({u - y[i] + r - x[i], y[i] - d + r - x[i], x[i] - l + u - y[i], x[i] - l + y[i] - d}));
    cout << res * 2 << ' '; // k = 3
    //k = 4
    for (int i = 4; i <= n; i++) {
        cout << 2 * (u - d + r - l) << ' ';
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
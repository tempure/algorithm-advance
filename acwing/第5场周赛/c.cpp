#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
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
//head

#define x first
#define y second


//MST + prim 输出方案

const int N = 2010;

int n;
pii q[N];
int wc[N], wk[N];
int dist[N], distp[N]; //distp记录最小生成树边的前驱点
bool st[N];
vi ans1;
vector<pii> ans2;

inline ll get_dist(int a, int b) {
    int dx = q[a].x - q[b].x;
    int dy = q[a].y - q[b].y;
    return 1ll * (abs(dx) + abs(dy)) * (wk[a] + wk[b]);
}

ll prim() {
    ll res = 0;
    dist[0] = 0, st[0] = true;
    for (int i =  1; i <= n; i++) dist[i] = wc[i]; //虚拟源点
    for (int i = 0; i < n; i++) {
        int t = -1;
        //第一次循环必然会先找一个点建立发电站 也就是直接和超级源点连接
        for (int j = 1; j <= n; j++)
            if (!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        st[t] = 1;
        res += dist[t];
        if (!distp[t]) ans1.pb(t); //说明是超级源点直接连 也就是直接建立发电站的位置
        else ans2.pb({distp[t], t});

        for (int j = 1; j <= n; j++)
            if (!st[j] && dist[j] > get_dist(t, j)) {
                dist[j] = get_dist(t, j);
                distp[j] = t; //与连通块连接的点 也就是最小生成树的一条边
            }
    }
    return res;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> q[i].x >> q[i].y;
    for (int i = 1; i <= n; i++) cin >> wc[i];
    for (int i = 1; i <= n; i++) cin >> wk[i];

    ll res = prim();
    cout << res << endl;
    cout << sz(ans1) << endl;
    for (auto x : ans1) cout << x << ' ';
    cout << endl;
    cout << sz(ans2) << endl;
    for (auto t : ans2)
        cout << t.x << ' ' << t.y << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while (t --) solve();

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
// #define x first
// #define y second
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


//https://atcoder.jp/contests/abc235/editorial/3263
//查询和原图边 一起排序
//但是只加原图的边，不加询问的边


const int N = 2e5 + 10, M = 2 * N;
int n, m, q;
// int cnt; //最小生成树的边数量 判断是否无解
int p[N];
vector<pair<int, string> > res;

struct Edge {
    int a, b, w;
    bool flag;
    int query_id; //询问的ID
    bool operator<(const Edge &u) {
        return w < u.w;
    }
} edges[M];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void kruskal() {
    sort(edges, edges + m + q);
    for (int i = 0; i < m + q; i++) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        bool f = edges[i].flag;
        int id = edges[i].query_id;
        a = find(a), b = find(b);
        if (a != b) {
            // res += w;
            // cnt ++;
            if (f) { //询问的边不加，原图的边才加入DSU
                res.pb({id, "Yes"});
            }
            else {
                p[a] = b;
            }
        }
        else if (f) {
            res.pb({id, "No"});
        }
    }
    // if (cnt != n - 1) puts("impossible");
    // else cout << res << endl;
}


void solve() {
    cin >> n >> m >> q;
    for (int i = 0; i <= n; i++) p[i] = i; //DSU init
    for (int i =  0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w, 0, 0x3f3f3f3f};
    }
    for (int i = m; i < m + q; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w, 1, i - m};
    }
    kruskal();
    sort(all(res));
    for (auto t : res) cout << t.second << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
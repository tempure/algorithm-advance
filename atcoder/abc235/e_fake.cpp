#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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

const int N = 2e5 + 10, M = 2 * N;

int cnt; //最小生成树的边数量 判断是否无解
int p[N];
int n, m, q, res;

struct Edge {
    int a, b, w;
    bool operator<(const Edge &u) {
        return w < u.w;
    }
} edges[M];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

set<pii> S;

void kruskal() {
    sort(edges, edges + m);
    for (int i = 0; i < m; i++) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        a = find(a), b = find(b);
        if (a != b) {
            res += w;
            p[a] = b;
            S.insert({a, b});
            S.insert({b, a});
            cnt ++;
        }
    }
    // if (cnt != n - 1) puts("impossible");
    // else cout << res << endl;
}



void solve() {
    cin >> n >> m >> q;
    for (int i = 0; i <= n; i++) p[i] = i;
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }
    for(int i= 0; i < q; i++){
        int a, b, c;
        cin >> a >> b >> c;
        // if()
    }
    kruskal();
    while (q --) {
        int a, b, c;
        cin >> a >> b >> c;
        if (S.count({a, b}) || S.count({b, a})) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
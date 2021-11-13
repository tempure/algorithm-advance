#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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

//用DSU存所有询问

const int N = 200010;

int n, m, k;
int p[N], col[N], cnt[N];
vector<int> S[N]; //所有连通块集合

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= n; i++) cin >> col[i];

    while (m --) {
        int a, b;
        cin >> a >> b; //query
        p[find(a)] = find(b);
    }
    for (int i = 1; i <= n; i++) S[find(i)].push_back(i);
    int res = 0;
    for (int i = 1; i <= n; i++)
        if (S[i].size()) {
            int t = 0; //max
            for (auto x : S[i]) t = max(t, ++cnt[col[x]]); //每个集合中次数最多的询问，颜色最多，把其他询问都变为这个询问的颜色即可
            res += S[i].size() - t;
            for (auto x : S[i]) -- cnt[col[x]]; //清空当前连通块的计数，计算下一个连通块
        }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
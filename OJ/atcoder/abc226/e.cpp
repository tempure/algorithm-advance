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
#define watch(x) cerr << (#x) << " is " << (x) << endl
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


//the proof is really complex

const int N = 200100, MOD = 998244353;
vector<int> e[N];
bool used[N];

int x, y; //vertex and edges;

void dfs(int k) {
    // if (used[k]) return;
    used[k] = true;
    x ++;
    y += e[k].size();
    for (int i = 0; i < e[k].size(); i++)
        if (!used[e[k][i]]) dfs(e[k][i]);
    // return;
}

void solve() {
    int n, m;
    ll ans = 1;
    cin >> n >> m;
    for (int i = 0; i < n; i++) used[i] = false;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        e[x - 1].pb(y - 1); //下标转换一下
        e[y - 1].pb(x - 1);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            x = 0;
            y = 0;
            dfs(i);
            if (y == 2 * x) ans = (ans * 2) % MOD;
            else {
                ans = 0;
                cout << 0 << endl;
                return;
            }
        }
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
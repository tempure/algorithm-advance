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

//https://atcoder.jp/contests/abc198/submissions/21662551
//https://atcoder.jp/contests/abc198/editorial/1081

const int N = 1e5 + 10;
int n;
int c[N]; //color
vi g[N]; //adj table
map<int, int> mp;
vi ans;

void dfs(int x, int p) {
    if (mp[c[x]] == 0) {
        ans.pb(x + 1); //当前颜色没出现过，该点可以存在答案中，点编号记得+1
    }
    mp[c[x]] ++;
    for (auto y : g[x]) {
        if (y == p) continue;
        dfs(y, x);
    }
    mp[c[x]] --;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--; //start from 0
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(0, -1);
    sort(all(ans));
    for (auto x : ans) cout << x << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
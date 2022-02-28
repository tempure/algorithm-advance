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

//这题好像没太懂题意是啥。。。
//官方题解：BFS https://atcoder.jp/contests/abc187/submissions/19103187
//懒标记线段树做法：https://cp-wiki.vercel.app/en/tutorial/atcoder/ABC187/#problem-e-through-path

void solve() {
    ll N;
    cin >> N;
    vector<pair<ll, ll>> edge(N - 1);
    vector<vector<ll>> g(N);
    for (ll i = 0; i < N - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
        edge[i] = {a, b};
    }
    vector<ll> depth(N, -1);
    depth[0] = 0;
    vector<ll> q = {0};
    while (q.size()) {
        ll at = q.back();
        q.pop_back();
        for (ll i : g[at]) if (depth[i] == -1) {
                depth[i] = depth[at] + 1;
                q.push_back(i);
            }
    }
    vector<ll> s(N);
    ll Q;
    cin >> Q;
    while (Q--) {
        ll t, e, x;
        cin >> t >> e >> x;
        auto [a, b] = edge[e - 1];
        if (depth[a] > depth[b]) {
            swap(a, b);
            t ^= 3;
        }
        if (t == 1) {
            s[0] += x;
            s[b] -= x;
        }
        else s[b] += x;
    }
    q = {0};
    while (q.size()) {
        ll at = q.back();
        q.pop_back();
        for (ll i : g[at]) if (depth[at] < depth[i]) {
                s[i] += s[at];
                q.push_back(i);
            }
    }
    for (ll i : s) cout << i << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
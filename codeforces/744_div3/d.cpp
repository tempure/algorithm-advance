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

void solve() {
    priority_queue<pii> q;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x > 0) q.push({x, i});
    }
    if (sz(q) <= 1) {
        cout << 0 << endl;
        return;
    }
    vector<pii> res;
    int ans = 0;
    while (sz(q) > 1) {
        auto t1 = q.top();
        q.pop();
        auto t2 = q.top();
        q.pop();
        // for (int i = 0; i < t2.x; i++) cout << t2.y << ' ' << t1.y << endl;
        res.push_back({t2.y, t1.y});
        // if ((t1.x - t2.x) != 0)q.push({t1.x - t2.x, t1.y});
        if (t1.x > 1) q.push({t1.x - 1, t1.y});
        if (t2.x > 1) q.push({t2.x - 1, t2.y});
        ans ++;
    }
    cout << ans << endl;
    if (ans == 0) return;
    if (sz(res))
        for (auto t : res) {
            cout << t.x << ' ' << t.y << endl;
        }
}


int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
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

pq<int> q;
const int INF = 0x3f3f3f3f;

void solve() {
    int a[4];
    char op[3];
    for (int i = 0; i < 4; i++) cin >> a[i];
    for (int i = 0; i < 3; i++)cin >> op[i];
    sort(a, a + 4);
    vi res;
    if (op[0] == '+') {
        res.pb(a[0] + a[1]);
        res.pb(a[2]);
        res.pb(a[3]);
        sort(all(res));
    }
    else if (op[1] == '*') {
        
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
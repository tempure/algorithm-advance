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

void solve() {
    queue<pii> q;
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int ty, c;
        scanf("%d%d", &ty, &c);
        if (ty == 1) {
            int x;
            scanf("%d", &x);
            q.push({x, c});
        } else {
            ll s = 0;
            while (c) {
                int d = min(c, q.front().fi);
                s += 1ll * d * q.front().se;
                q.front().fi -= d;
                c -= d;
                if (q.front().fi == 0) q.pop();
            }
            printf("%lld\n", s);
        }
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
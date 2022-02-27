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

//https://atcoder.jp/contests/abc241/submissions/29692960

void solve() {
    multiset<ll> A;
    int q;
    cin >> q;
    while (q--) {
        ll op, x, k;
        cin >> op;
        if (op == 1) {
            cin >> x;
            A.insert(x);
        } else if (op == 2) {
            cin >> x >> k;
            auto it = A.upper_bound(x);
            for (; k > 0 && it != A.begin(); --k) --it;
            if (k > 0) {
                cout << -1 << '\n';
            } else {
                cout << *it << '\n';
            }
        } else {
            cin >> x >> k;
            auto it = A.lower_bound(x);
            if (it == A.end()) {
                cout << -1 << '\n';
            } else {
                for (; k > 1 && std::next(it) != A.end(); --k) ++it;
                if (k > 1) {
                    cout << -1 << '\n';
                } else {
                    cout << *it << '\n';
                }
            }
        }
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
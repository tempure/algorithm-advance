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

#define int long long

int res = 0;

void divide(int x) {
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, s ++ ;
            //t*(t+1)/2 = s 不太好做
            //直接暴力 1 + 2 + ...k <= s 求k
            for (int j = 1; j < 10000; j++) {
                if (s < j) break;
                res++, s -= j;
            }
        }
    if (x > 1) res++;
    // cout << res << endl;
}

void solve() {
    ll n;
    cin >> n;
    divide(n);
    cout << res << endl;
}

signed main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
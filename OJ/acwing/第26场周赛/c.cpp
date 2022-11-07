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

//https://www.acwing.com/activity/content/code/content/2071141/

const int N = 100010;
int T, K;
int f[N];

void solve() {
    cin >> T >> K;
    f[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = f[i - 1];
        if (i >= K) f[i] = (f[i - 1] + f[i - K]) % mod;
    }
    for (int i = 1; i < N; i++) f[i] = (f[i] + f[i - 1]) % mod;
    while (T --) {
        int l, r;
        cin >> l >> r;
        cout << (f[r] - f[l - 1] + mod) % mod << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
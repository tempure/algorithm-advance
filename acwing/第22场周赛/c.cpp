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

//https://www.acwing.com/solution/content/8867/ 盒子允许空的组合数题解
//https://www.acwing.com/solution/content/71328/ 本题题解

const int N = 1e5 + 10;

int fact[N], infact[N]; //阶乘和逆元

void solve() {
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = 1ll * fact[i - 1] * i % mod;
        infact[i] = 1ll * infact[i - 1] * powmod(i, mod - 2) % mod; //费马小定理，素数取模
    }
    int n, m, a, b;
    cin >> n >> m;
    a = 2 * m + n - 1, b = n - 1;
    cout << 1ll * fact[a] * infact[b] % mod * infact[a - b] % mod;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
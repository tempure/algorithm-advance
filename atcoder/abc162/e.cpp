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

//https://img.atcoder.jp/abc162/editorial.pdf
//https://blog.51cto.com/u_15067267/4110591
//https://www.cnblogs.com/zcr-blog/p/12717719.html
//会包含gcd=d*2,gcd=d*3...的答案，所以要减去,实现的时候倒着循环即可。

//题解第一步求出的可能还是 2X, 3X 作为GCD的，在后面较大的X可能会重复，要减去
//可以莫反 但是我不会....

const int N = 1e5 + 5, MD = 1e9 + 7;
int f[N];
ll qpow(ll a, ll b) {
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % MD) if (b & 1) ans = ans * a % MD;
    return ans;
}
void add(int &x, int y) {
    x += y;
    if (x >= MD) x -= MD;
    if (x < 0) x += MD;
}
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, k;
    scanf("%d%d", &n, &k);
    cin >> n >> k;
    for (int i = k; i >= 1; i--) {
        f[i] = qpow(k / i, n);
        for (int j = 2 * i; j <= k; j += i)
            add(f[i], -f[j]);
    }
    int ans = 0;
    for (int i = 1; i <= k; i++)
        add(ans, 1LL * f[i]*i % MD);

    cout << ans;
}
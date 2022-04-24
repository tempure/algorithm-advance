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
    int a, b, c;
    int d, e, f;
    int x;
    cin >> a >> b >> c >> d >> e >> f >> x;
    int lena = 0, lenb = 0;
    lena = (x / (a + c)) * b * a + min(a, x % (a + c)) * b ;
    lenb = (x / (d + f)) * e * d + min(d, x % (d + f)) * e ;
    // cout << lena << endl;
    // cout << lenb << endl;
    if (lena > lenb) puts("Takahashi");
    else if (lena < lenb) puts("Aoki");
    else puts("Draw");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
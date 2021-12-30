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

const int N = 5e4 + 10;
ll a[N]; //prefix sum
int n;;

void solve() {
    cin >> n;
    int x;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> x;
    for (int i = 1; i <= n; i++) a[i] -= x;
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];
    int ans = 0;
    for (int l = 1, r; l <= n; l = r + 2) { //长度最少为2（？）
        ll cur = a[l - 1];
        for (r = l; r < n && a[r + 1] - cur >= 0; r++) { //子段和>=0才行
            cur = max(cur, a[r]);
        }
        ans += r - l + 1;
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
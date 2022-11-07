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

//不要用 double d = (a[j] - a[i]) / (j-i) 有精度问题，等式两边改为乘法比较

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    int res = n - 1;
    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            cnt = 0;
            // long double d = 1.0 * (a[j] - a[i]) / (j - i);
            for (int k = 0; k < j; k++) {
                if (a[k] * (j - i) != a[j] * (j - i) - (j - k) * (a[j] - a[i])) cnt++;
            }
            for (int p = j + 1; p < n; p++) {
                if (a[p] * (j - i) != a[j] * (j - i) + (p - j) * (a[j] - a[i])) cnt++;
            }
            res = min(res, cnt);
        }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
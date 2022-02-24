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

//https://codeforces.com/contest/1641/submission/147414901

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<bool> used(n, false);
    int ans = 0;
    int j = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        if (used[i]) {
            continue;
        }
        if (a[i] % x == 0) {
            int f = a[i] / x;
            while (j >= 0 && (used[j] || a[j] > f)) {
                j -= 1;
            }
            if (j >= 0 && !used[j] && a[j] == f) {
                used[i] = true;
                used[j] = true;
                ans += 1;
            }
        }
    }
    cout << n - 2 * ans << '\n';
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
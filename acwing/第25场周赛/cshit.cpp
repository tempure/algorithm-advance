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

const int N = 2e5 + 10;
int s[N];
int color[N];

void solve() {
    int n, m, k;
    int res = 0;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        int ci; cin >> ci;
        color[i] = ci;
        s[ci] ++;
    }
    while (m --) {
        int l, r;
        cin >> l >> r;
        if (color[l] != color[r]) {
            if (s[color[l]] > s[color[r]]) {
                color[r] = color[l];
                res++;
                s[color[l]] ++;
                s[color[r]] --;
            }
            else {
                color[l] = color[r];
                res++;
                s[color[l]] ++;
                s[color[r]] --;
            }
        }
    }
    // for (int i = 1; i <= n; i++) cout << s[i] << ' ' <<  endl;
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
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

const int N = 1e6 + 5, INF = 0x3f3f3f3f;

int n;
string s;

void solve() {
    cin >> n >> s;
    int ans = INF;
    for (int i = 0; i < n; i++) {
        vi f(3, 0);
        f[s[i] - 'a'] ++;
        for (int j = i + 1; j < min(n, i + 7); j++) {
            f[s[j] - 'a']++;
            if (f[0] > f[1] && f[0] > f[2])
                ans = min(ans, j - i + 1);
        }
    }
    if (ans == INF) ans = -1;
    cout << ans << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
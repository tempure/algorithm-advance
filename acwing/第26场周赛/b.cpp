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

const int N = 1e5 + 10, M = 26;

int n;
char str[N];
int last[M],  d[M];

void solve() {
    cin >> str + 1;
    n = strlen(str + 1);
    for (int i = 1; i <= n; i++) {
        int x = str[i] - 'a';
        d[x] = max(d[x], i - last[x]);
        last[x] = i;
    }
    for (int i = 0; i < 26; i++) //结尾
        d[i] = max(d[i], n + 1 - last[i]);

    int res = N + 1;
    for (int i =  0; i < 26; i++)
        res = min(res, d[i]);
    cout << res << '\n';
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
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

char a[110][110];
int n, m, x, y;
int ans;

int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
bool st[110][110];

void dfs(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int X = x + dx[i], Y = y + dy[i];
        if (X >= 0 && X < n && Y >= 0 && Y < m) {
            if (a[X][Y] == '#') continue;
            if (st[X][Y]) continue;
            st[X][Y] = true;
            ans++;
            cout << X << ' ' << Y << endl;
            dfs(X, Y);
        }
    }
}

void solve() {
    cin >> n >> m >> x >> y;
    for (int i = 0; i < n; i++) cin >> a[i];
    dfs(x - 1, y - 1);
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
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

//这标程和他题解描述的思路为什么不一致（?)

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j)
            a[i][j] = s[j] - '0';
    }
    vector<array<int, 4>> ans;
    if (a[0][0] == 1) {
        cout << -1 << '\n';
        return;
    }

    for (int j = m - 1; j >= 0; --j) {
        for (int i = n - 1; i >= 0; --i) {
            if (a[i][j]) {
                if (i != 0) {
                    ans.push_back({i, j + 1, i + 1, j + 1});
                } else {
                    ans.push_back({i + 1, j, i + 1, j + 1});
                }
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i[0] << ' ' << i[1] << ' ' << i[2] << ' ' << i[3] << '\n';
    }
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
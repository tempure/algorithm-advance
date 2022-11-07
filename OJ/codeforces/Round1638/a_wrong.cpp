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

//只能reverse一次.....

void solve() {
    int n;
    cin >> n;
    vi v(n);
    vi res(n);
    for (auto &x : res) x = 0x3f3f3f3f;
    for (auto & x : v) cin >> x;
    for (int i = 0; i <= n; i++)
        for (int j = i; j <= n; j++) {
            vector<int> temp = v;
            temp.resize(n);
            reverse(temp.begin() + i, temp.begin() + j);
            // for (auto t : temp) cout << t << ' ';
            // puts("");
            res = min(res, temp);
        }
    for (auto t : res) cout << t << ' ';
    puts("");
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
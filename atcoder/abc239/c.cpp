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
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    bool flag = false;
    if (abs(x1 - x2) == 1 && (abs(y1 - y2) == 1 || abs(y1 - y2) == 3)) flag = true;
    if (x1 == x2 && (abs(y1 - y2) == 2 || abs(y1 - y2) == 4)) flag = true;
    if (abs(x1 - x2) == 3 && (abs(y1 - y2) == 1 || abs(y1 - y2) == 3)) flag = true;
    if (abs(x1 - x2) == 4 && (abs(y1 - y2) == 2 || y1 == y2)) flag = true;
    if (abs(x1 - x2) == 2 && y1 == y2) flag = true;

    if (flag) puts("Yes");
    else puts("No");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
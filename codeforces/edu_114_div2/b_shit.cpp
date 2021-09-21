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

void solve() {
    int a[4];
    int m;
    for (int i = 1; i <= 3; i++) cin >> a[i];
    cin >> m;

    sort(a + 1, a + 4);
    if (a[3] >= 2 * m) a[3] -= 2 * m;
    else {
        if (a[3] & 1) a[3] = 1, m -= (a[3] - 1 ) / 2;
        else m -= a[3] / 2;
    }
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
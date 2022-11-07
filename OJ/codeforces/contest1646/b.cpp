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

//注意可以不染色。。。题意别搞混

void solve() {
    int n;
    cin >> n;
    vi a(n);
    ll sum = 0;
    for (auto &x : a) {
        cin >> x;
        sum += x;
    }
    sort(all(a));
    reverse(all(a));
    ll presum = 0, sufsum = 0;
    for (int i = 0, k = n - 1; i < k; i ++, k--) {
        presum += a[i];
        sufsum += a[k];
        if (k - 1 > i) if (presum > sufsum + a[k - 1]) {
                puts("YES");
                return;
            }
    }
    puts("NO");
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
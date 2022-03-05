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

//https://blog.csdn.net/pfccWang/article/details/77984827

int num[30000];
vector<int> v;
int isable[30000];

void solve() {
    int n = 28123;
    memset(num, 0, sizeof(num));
    memset(isable, 0, sizeof(num));
    for (int i = 1; i <= n; i++) {
        for (int j = i * 2; j <= n; j += i) {
            num[j] += i;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (num[i] > i) {
            v.push_back(i);
        }
    }
    for (int i = 0, maxn = v.size(); i < maxn; i++) {
        for (int j = i; j < maxn && v[i] + v[j] <= n; j++) {
            isable[v[i] + v[j]] = 1;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (isable[i] == 0) ans += i;
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
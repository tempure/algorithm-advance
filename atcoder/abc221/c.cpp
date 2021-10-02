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

//暴力枚举 最多有(n-1) *n! / 2 种分割方法，不考虑前导0
//所以直接枚举所有排列，然后每个排列都(n-1)个位置分割求出最大值

void solve() {
    string n;
    cin >> n;
    sort(all(n));
    int ans = 0;
    do {
        for (int i = 1; i < sz(n); i++) {
            string l = "", r = "";
            for (int j = 0; j < i; j++) l += n[j];
            for (int j = i; j < sz(n); j++) r += n[j];
            ans = max(ans, stoi(l) * stoi(r));
        }
    } while (next_permutation(all(n)));
    cout << ans << endl;
}


int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
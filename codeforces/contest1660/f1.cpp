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

//https://blog.csdn.net/m0_62325831/article/details/123889298
//暴力
/*
一次操作的结果是 ‘-’ 的数量减2，’+’ 的数量加1，所以一开始’-’ 和 '+'号的差值必须是3的倍数，
操作数为差值除以3，并且要满足操作数小于连续的 ‘-’ 出现的次数。时间复杂度为 O(n^2)
*/

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int pos = 0, neg = 0, con = 0;
        bool pre = 1;
        for (int j = i; j < n; ++j) {
            if (s[j] == '+') pos++;
            if (s[j] == '-') neg++;
            if (pos > neg || (neg - pos) % 3) {
                pre = 0;
                continue;
            }
            if (pre) {
                pre = 0;
            } else if (s[j] == '-' && s[j - 1] == '-') {
                con++;
                pre = 1;
            }
            if ((neg - pos) / 3 <= con) {
                ans++;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
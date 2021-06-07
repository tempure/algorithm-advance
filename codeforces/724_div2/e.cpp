#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
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

/*
选一个#的子集，填上0，那么剩余的位置只有唯一填法，考虑多源BFS的原理
特殊情况：所有位置都是#，那么不能选空集，至少得有一个0才行，因为如果所有都大于0，那么必然存在一个最小正数
这个正数周围没有比它小的
*/

void solve() {
    int n, m;
    cin >> n >> m;
    ll res = 1;
    bool has = false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char c ; cin >> c;
            if (c == '0') has = true;
            else {
                res = res * 2 % mod;
            }
        }
    if (has) cout << res << endl;
    else cout << res - 1 << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while (t --) solve();

    return 0;
}
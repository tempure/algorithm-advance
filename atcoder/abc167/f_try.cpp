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

//考虑

/*
2
)(
()

就不行，，
*/

void solve() {
    int n;
    cin >> n;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        int l = 0, r = 0;
        string s;
        cin >> s;
        for (int i = 0; s[i]; i++) {
            if (s[i] == '(') l ++ ;
            else r++;
        }
        res += l - r;
    }
    if (res == 0) puts("Yes");
    else puts("No");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
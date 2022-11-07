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
    ll a, b;
    cin >> a >> b;
    ll mmin = min(a, b);
    ll mmax = max(a, b);
    ll res = 0;
    if (a == 0 || b == 0) {
        res = 0;
    }
    else if ( a < 4 && b < 4 && a && b) {
        res = 1;
    }
    // else if (a < 4 || b < 4) {
    //     // else{
    //     res = min(mmax / 4, mmin);
    // }
    // else if (a > 4 && b > 4) {
    else {
        // if (mmax >= 3 * mmin) {
        //     res = mmin;
        // }
        // else {
        mmin -= mmax / 3;
        if (mmin > 0) {
            res = mmax / 3;

            ll tmp = mmin / 2;
            mmax -= tmp * 2;
            int res1 = tmp;
            if (mmax >= 3 && mmin % 2 > 0) res1 ++;
            res += res1;
        }
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
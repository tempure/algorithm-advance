#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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

// const int N = 2e5 + 10;

int mex(vector<int> & a) {
    set<int> S;
    for (auto t : a) S.insert(t);
    for (int i = 0; ; i++) {
        if (!S.count(i)) {
            return i;
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vi a(n);
    vi b;
    for (int i = 0; i < n; i++) cin >> a[i];

    while (sz(a) > 0) {
        vi temp;
        int mexnum = -1;
        int pos = -1;
        int mexc = -1;
        for (int i = 0; i < sz(a); i++) {
            temp.pb(a[i]);
            if (mexc != -1 && a[i] != mexc) continue;
            mexc = mex(temp);
            if (mexc > mexnum) {
                pos = i;
                mexnum = mexc;
            }
        }
        // cout << pos << endl;
        b.pb(mexnum);
        a.erase(a.begin(), a.begin() + pos + 1);
    }
    cout << sz(b) << endl;
    for (auto t : b) cout << t << ' ';
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
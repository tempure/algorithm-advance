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
#define watch(x) cerr << (#x) << " is " << (x) << endl
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
// ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

//https://codeforces.com/blog/entry/97927

void solve() {
    ll n; cin >> n;
    vector <ll> a(n + 1);

    ll s1 = 0, s2 = 0;

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        if (i % 2 == 1) s1 = gcd(s1, a[i]);
        else s2 = gcd(s2, a[i]);
    }
    bool h1 = true, h2 = true;
    for (int i = 1; i <= n; i += 2) {
        if (a[i] % s2 == 0) h2 = false;
    }
    for (int i = 2; i <= n; i += 2) {
        if (a[i] % s1 == 0) h1 = false;
    }
    if (h1) {
        cout << s1 << "\n";
        return;
    }
    if (h2) {
        cout << s2 << "\n";
        return;
    }
    cout << "0\n";
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
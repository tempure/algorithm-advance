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


const int N = 2e5 + 10;
// typedef pair<ll, int> pli;
// pli a[N];

map<ll, ll> m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    // for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;

    for (int i =  0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        m[a] += b;
    }

    ll res = k;

    bool flag = true;

    for (auto t : m) {
        if (res < t.first) {
            flag = false;
            cout << res << endl;
            break;
        }
        res += t.second;
    }

    if (flag) cout << res << endl;

    return 0;
}
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

const int N = 1e5 + 10;
vi a;
int n, k;

struct Node {
    vi t;
    int key;
    bool operator< (const Node &A) {
        return key < A.key;
    }
} tt[N];

bool check(int val) {
    for (int i = 0; i < sz(a); i++) {
        if (i + val <= a[i]) return false;
    }
    return true;
}

void solve() {
    a.clear();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        tt[i].t.clear();
        tt[i].key = 0xcfcfcfcf;
        for (int j = 1; j <= k; j++) {
            int x; cin >> x;
            tt[i].t.pb(x);
            tt[i].key = max(tt[i].key, x - j);
        }
    }

    sort(tt + 1, tt + n + 1);
    for (int i = 1; i <= n; i++)
        for (auto it : tt[i].t) a.pb(it);

    int l = 1, r = 1e9 + 50;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
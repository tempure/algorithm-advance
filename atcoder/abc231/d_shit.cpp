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
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

const int N = 1e5 + 10;
int n, m;
int in[N], out[N];

void solve() {
    cin >> n >> m;
    // memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a]++, in[b]++;
    }
    int cnt = 0;
    vi temp;
    for (int i = 1; i <= n; i++) {
        if (in[i] > 2 || out[i] > 2) {
            puts("No");
            return;
        }
        if (in[i] < 2 || out[i] < 2) {
            temp.pb(i);
            cnt ++;
        }
        if (cnt > 2) {
            puts("No");
            return;
        }
        if (i != temp[0] && i != temp[1] && (in[i] != 2 || out[i] != 2)) {
            puts("No");
            return;
        }
    }
    puts("Yes");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
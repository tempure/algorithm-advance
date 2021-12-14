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

//三置换 如果存在2以上相同元素true，换个数为偶数 true

const int N = 1010000;
int n, a[N], f[N];

int find(int x) {
    if (x != f[x])
        f[x] = find(f[x]);
    return f[x];
}

void solve() {
    cin >> n;
    set<int> S;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        S.insert(a[i]);
    }
    if (sz(S) < n) {
        puts("YES");
        return;
    }
    for (int i = 1; i <= n; i++) f[i] = i;
    int cyc = n;
    for (int i = 1; i <= n; i++)
        if (find(i) == find(a[i])) --cyc;
        else {
            f[find(i)] = find(a[i]);
        }
    if (cyc % 2 == 0) {
        puts("YES");
    }
    else puts("NO");
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
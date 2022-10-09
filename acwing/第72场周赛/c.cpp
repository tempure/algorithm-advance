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

/*
每个点出度为1，就是基环树问题，如果环上有链那么无解
https://www.acwing.com/video/4461/

对于视频里面补充说明一点：由于图中只有环，假设环长为L, 对于L为偶数的 L/2整数倍, 以及奇数就是L的整数倍的取值
是唯一的解，比如偶数来说，除了 L/2 的整数倍，其余所有的t都不符合题目要求，都走不回来，只能取这个值, 就是最小的唯一解
*/
const int N = 110;
int n;
int d[N], p[N], s[N]; // d[N]  每个点到底入度

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

ll work() {
    for (int i = 1; i <= n; i++)
        if (d[i] != 1) return -1;
    ll res = 1;
    for (int i = 1; i <= n; i++)
        if (p[i] == i) {
            int len = s[i];
            if (len % 2 == 0) len /= 2;
            res = res * len / gcd(res, len); //LCM
        }
    return res;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) p[i] = i, s[i] = 1; //DSU
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        d[x] ++;
        int a = find(i), b = find(x);
        if (a != b) {
            s[b] += s[a];
            p[a] = b;
        }
    }
    cout << work() << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
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

//最多集合不能超过3个数
//证明：https://www.acwing.com/video/4196/
//此题卡常，需要手写 hash

const int N = 2e5 + 10, M = 1999997, INF = 0x3f3f3f3f;

int n;
int q[N], h[M];

int find(int x) { //返回哈希数组中的下标
    int t = (x % M + M) % M;
    while (h[t] != INF && h[t] != x)
        if ( ++ t == M)
            t = 0;
    return t;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> q[i];
    sort(q, q + n);

    memset(h, 0x3f, sizeof h);

    int res[3], s[3];
    int rt = 0, st = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 30; j++) { //次幂
            int d = 1 << j;
            s[0] = q[i], st = 1;
            for (int k = 1; k <= 2; k ++ ) {
                int x = q[i] - d * k;
                if (h[find(x)] == INF) break;
                s[st++] = x;
            }
            if (rt < st) {
                rt = st;
                memcpy(res, s, sizeof s);
                if (rt == 3) break;
            }
        }
        if (rt == 3) break; //已经找到合法解
        h[find(q[i])] = q[i];
    }
    //找不到3个满足的数，那么就只有一个数的集合了
    //此时复杂度是最坏情况，不会break直到遍历所有数
    //但是 rt 一直不会被更新
    cout << rt << endl;
    for (int i = 0; i < rt; i++)
        cout << res[i] << ' ';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
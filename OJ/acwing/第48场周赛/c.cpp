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
typedef pair<int, int> PII;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

//https://www.acwing.com/video/3836/
//这题卡 unordered_map, 注意初始化大小
//区间合并/并查集 都能做
//并查集合并的时候，一个区间内的点都向最右端点合并，最右端点是当前区间的root

#define x first
#define y second

const int N = 200010, MOD = 998244353;

int n;
PII q[N];

void solve() {
    scanf("%d", &n);

    unordered_map<int, int> L(300000), R(300000); //注意初始化大小 防止被卡
    for (int i = 1; i <= n; i ++ ) {
        int a;
        scanf("%d", &a);
        R[a] = i;
        if (!L.count(a)) L[a] = i;
    }

    int m = 0;
    for (auto& [k, v] : L) q[m ++ ] = {L[k], R[k]};

    sort(q, q + m);

    int cnt = 0, st = -1, ed = -1;
    for (int i = 0; i < m; i ++ )
        if (q[i].x <= ed) ed = max(ed, q[i].y);
        else {
            cnt ++ ;
            st = q[i].x, ed = q[i].y;
        }

    int res = 1;
    for (int i = 0; i < cnt - 1; i ++ )
        res = res * 2 % MOD;

    printf("%d\n", res);
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
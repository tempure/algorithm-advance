#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
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

/*
细节：
0号虚拟源点，第一个作用是保证所有点取值的下届，比如>=1，那就连1边权
第二个作用是使图连通，不用将所有点入队列或者入栈

求最小值就是跑最长路，很容易理解，让点权最小，那么迭代次数就会很多，这样才能花费很多条边迭代到上界结束，有正环就无解 说明不等式组出现了矛盾
同理最大值就跑最短路, 这样边权和就会最小，点权和就会最大，dist[i]就是xi的值, 边权越大不等式链很快就能达到上界结束，存在负环说明无解
*/

const int N = 1e5 + 10, M = 3 * N; // 差分约束开3倍边 最坏的情况边数就是A=B 加上虚拟原点
int n, k;
int h[N], e[M], w[M], ne[M], idx;
ll dist[N]; //1 + 2 + 3 + .. N^2级别
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool spfa() {
    memset(dist, 0xcf, sizeof dist);
    int hh = 0, tt = 1;
    dist[0] = 0;
    q[0] = 0;
    st[0] = true;

    while (hh != tt) {
        int t = q[--tt];
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n + 1) return true;
                if (!st[j]) {
                    q[tt++] = j;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

void solve() {
    cin >> n >> k;
    memset(h, -1, sizeof h);
    while (k --) {
        int x, a, b;
        cin >> x >> a >> b;
        if (x == 1) add(b, a, 0), add(a, b, 0);
        else if (x == 2) add(a, b, 1);
        else if (x == 3) add(b, a, 0);
        else if (x == 4) add(b, a, 1);
        else add(a, b, 0);
    }
    for (int i = 1; i <= n; i++) add(0, i, 1); // xi >= 0 + 1
    if (spfa()) cout << -1 << endl;
    else {
        ll res = 0;
        for (int i = 1; i <= n; i++) res += dist[i];
        cout << res << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}
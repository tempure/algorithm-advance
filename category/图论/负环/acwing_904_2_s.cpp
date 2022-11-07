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

const int N = 510, M = 6010;

/*
初始全部入队原因：防止图不连通，所有点初始都入队相当于有一个虚拟源点，向所有点都连边，边权为0，这样第一次做spfa
就将所有点入队了，这是等价的，正确性不变。这种做法也等价于从任何一个点开始找负环都可以。

所有dist初始为0的正确性：因为负环存在必然会某些点的dist被迭代到负无穷，不影响cnt边数的统计

trick技巧：当所有点入队的次数超过2*n时，就认为存在负环，防止spfa超时
*/

int n, m1, m2; //单向以及双向边的数量
int h[N], ne[M], w[M], idx, e[M];
int dist[N];
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

//判负环的spfa是双端队列，下标都是后缀++，注意初始对头队尾都是0
bool spfa() {
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    memset(dist, 0, sizeof dist);

    int hh = 0, tt = 0;
    for (int i = 1; i <= n; i++) {
        q[tt++] = i;
        st[i] = true;
    }
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n) return true;
                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

void solve() {
    memset(h, -1, sizeof h);
    idx = 0;
    cin >> n >> m1 >> m2;
    while (m1 -- ) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    while (m2 --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, -c);
    }
    if (spfa()) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}
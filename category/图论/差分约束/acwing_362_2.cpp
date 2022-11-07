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

//此题一定存在解，因为可以直接跑最长路就行了 不用判负环
//所有点都选肯定时一种解 所以必然存在解，不需要cnt数组
//连通：所有点都向前一个点连边，图必然连通,不需要全部入栈/队列或者加虚拟源点这种操作。
//所有点都后移+1， 变成1~50001中选,这样0空出来方便前缀和

const int N = 5e5 + 10, M = N * 3; //有三种情况，每种都要加N条边
int n;
int h[N], e[M], ne[M], w[M], idx;
int dist[N];
int q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void spfa() {
    int hh = 0, tt = 1;
    memset(dist, 0xcf, sizeof dist);
    dist[0] = 0, q[0] = 0;
    st[0] = true;

    while (hh <= tt) {
        int t = q[--tt];
        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                }
            }
        }
    }
}

void solve() {
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= 50001; i++) {
        add(i - 1, i, 0);
        add(i, i - 1, -1);
    }
    while (n -- ) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a - 1, b, c);
    }
    spfa();
    cout << dist[50001] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}
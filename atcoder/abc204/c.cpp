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

//每个点为起点暴力 bfs 一次计数即可

const int N = 2010, M = N * (N - 1) / 2;
int h[N], e[M], ne[M], idx;
int n, m;
bool v[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int bfs(int u) {
    int res = 1;
    queue<int> q;
    q.push(u);
    v[u] = 1;

    while (q.size()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; ~i ; i = ne[i]) {
            int j = e[i];
            if (v[j]) continue;
            v[j] = 1;
            res++;
            q.push(j);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(h, - 1, sizeof h);

    cin >> n >> m;
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        memset(v, 0, sizeof v);
        res += bfs(i);
    }
    cout << res << endl;

    return 0;
}
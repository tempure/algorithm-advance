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
//snippet-head

const int N = 110, M = N * N;
int d[N];
int path[N];
int h[N], e[M], ne[M], idx;
int cnt;

int n;
queue<int> q;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void topsort() {
    for (int i = 1; i <= n; i++)
        if (d[i] == 0) q.push(i);

    while (q.size()) {
        int t = q.front();
        q.pop();
        path[cnt++] = t;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) q.push(j);
        }
    }
}

int main() {
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int x;
        while (cin >> x && x) {
            add(i, x);
            d[x] ++;
        }
    }

    topsort();

    for (int i = 0; i < cnt; i++) cout << path[i] << ' ';
    cout << endl;

    return 0;
}
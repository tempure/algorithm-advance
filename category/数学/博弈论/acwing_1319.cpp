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

const int N = 2010, M = 6010;

int n, m, k;
int h[N], e[M], ne[M], idx;
int sg[N];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

int SG(int u) {
    if (sg[u] != -1) return sg[u];
    set<int> s;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        s.insert(SG(j));
    }

    for (int i = 0; ; i++)
        if (!s.count(i)) {
            sg[u] = i;
            break;
        }
    return sg[u];
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    memset(h, -1, sizeof h);
    memset(sg, -1, sizeof sg);
    for (int i = 0; i < m; i++) {
        int a, b ;
        scanf("%d%d", &a, &b);
        add(a, b);
    }

    int res = 0;
    for (int i = 0; i < k; i++) {
        int u; scanf("%d", &u);
        res ^= SG(u);
    }

    if (res) puts("win");
    else puts("lose");

    return 0;
}
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

//同时维护size以及节点到root节点的距离

const int N = 30010;
int p[N], sz[N], d[N];
int m;

int find(int x) {
    //维护路径距离的find函数
    if (p[x] != x) {
        int root = find(p[x]);
        d[x] += d[p[x]];
        p[x] = root;
    }
    return p[x];
}

int main() {
    scanf("%d", &m);

    for (int i = 1; i <= N; i++) {
        p[i] = i;
        sz[i] = 1;
    }

    while (m --) {
        char op[2];
        int a, b;
        scanf("%s%d%d", &op, &a, &b);
        if (op[0] == 'M') {
            int pa = find(a), pb = find(b);
            d[pa] = sz[pb]; //将a接到b的下边
            sz[pb] += sz[pa];

            //最后才改变root注意 先操作合并d和sz
            p[pa] = pb;
        }
        else {
            int pa = find(a),  pb = find(b);
            if (pa != pb) puts("-1");
            //a和b两个查询的点相同那就返回0 特判一下 可以直接用max写在一起
            else printf("%d\n", max(0, abs(d[a] - d[b]) - 1));
        }
    }

    return 0;
}
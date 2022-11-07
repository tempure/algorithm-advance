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

//每次连边的时候 如果要连边的2个端点已经在同一个集合中 那么就说明存在环了
//路径压缩+按秩合并 才能常熟复杂度，如果只路径压缩 是log复杂度每次find操作

const int N = 210, M = N * N;

int n, m;
int p[M]; //地图一共N * N 个点


int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int get(int x, int y) {
    return x * n + y;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n * n; i++) p[i] = i;

    int res = 0;
    for (int i = 1; i <= m; i++) {
        int x, y;
        char d;
        cin >> x >> y >> d;
        x --, y -- ; //下标从0开始 比较好写
        int a = get(x, y);
        int b;
        if (d == 'D') b = get(x + 1, y);
        else b = get(x, y + 1);

        int pa = find(a), pb = find(b);
        if (pa == pb) {
            res = i;
            break;
        }
        p[pa] = pb;
    }

    if (!res) puts("draw");
    else cout << res << endl;
}
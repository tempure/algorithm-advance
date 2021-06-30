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

#define x first
#define y second

//寻找一个最小的d值 然后图中小于等于d的点相连 也就是删除距离大于d的边 那么就出现了若干个连通块
//如果出现连通块个数不超过 k 那么说明d合法
//注意题意:只有 两个 点都有设备 才能进行通信
//kruskal 算法是递增求连通块的边 初始的连通块是所有点 当连通块个数递减到k时 结束 此时的边权就是答案

const int N = 510, M = N * N / 2; //将所有边排序，要求所有点对的距离
int p[N];
pii q[N];

struct Edge {
    int a, b;
    double w;
    bool operator< (const Edge &t) {
        return w < t.w;
    }
} e[M];

int n;
int k;
int m; //边数

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

double get_dist(pii a, pii b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void solve() {
    cin >> n >> k;
    for (int i =  0; i < n; i++) cin >> q[i].x >> q[i].y;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++) //注意kruskal只加单向边即可
            e[m++] = {i, j, get_dist(q[i], q[j])};
    sort(e, e + m);
    for (int i = 0; i < n; i++) p[i] = i;
    int cnt = n; //初始连通块个数
    double res = 0;
    for (int i = 0; i < m; i++) {
        if (cnt <= k) break;
        int a = find(e[i].a), b = find(e[i].b);
        double w = e[i].w;
        if (a != b) {
            p[a] = b;
            cnt --;
            res = w;
        }
    }
    printf("%.2lf", res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
#define endl '\n'
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

//https://www.acwing.com/video/3637/

//小数据范围暴力+bitset 优化
//暴力判断每个点和所有圆的圆内和圆外的关系

//大数据范围转换为求LCA和树上最短路问题


//如何暴力：对于每个点，都求出其和所有圆的位置关系，如果不在内就是1，否则是0，状态用一个bitset来存
//对于一个询问中的2个点，答案就是2个点对应的bitset的不同位的个数，直接异或

const int N = 1010;
int n, m, Q;
pii p[N], c[N]; //点坐标 圆心坐标
int r[N];
bitset<N> st[N];

ll sqr(ll x) {
    return x * x;
}

int check(int a, int b) { //点a和圆b的位置关系
    ll dx = p[a].x - c[b].x;
    ll dy = p[a].y - c[b].y;
    if (sqr(dx) + sqr(dy) > sqr(r[b])) return 1; //不在圆内
    else return 0;
}

void solve() {
    cin >> n >> m >> Q;
    for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;
    for (int i = 0; i < m; i++) cin >> r[i] >> c[i].x >> c[i].y;

    for (int i =  1; i <= n; i++)
        for (int j =  0; j < m; j++)
            st[i][j] = check(i, j);

    while (Q --) {
        int a, b;
        cin >> a >> b;
        cout << (st[a] ^ st[b]).count() << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
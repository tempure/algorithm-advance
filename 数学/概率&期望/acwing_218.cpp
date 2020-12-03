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

const int N = 14;
const double INF = 1e20;
int A, B, C, D;
double f[N][N][N][N][5][5];

double dp(int a, int b, int c, int d, int x, int y) {
    double &v = f[a][b][c][d][x][y];
    if (v >= 0) return v; //记忆化
    int as = a + (x == 0) + (y == 0);
    int bs = b + (x == 1) + (y == 1);
    int cs = c + (x == 2) + (y == 2);
    int ds = d + (x == 3) + (y == 3);
    if (as >= A && bs >= B && cs >= C && ds >= D) return v = 0; //终点
    if (a > 13 || b > 13 || c > 13 || d > 13) return v = INF; //输入有误数据

    int sum = a + b + c + d + (x != 4) + (y != 4); //当前已经翻开的牌总数
    v = 1;  //初始化当前状态 开始计算
    sum = 54 - sum; //剩余牌数
    if (sum <= 0) return v = INF;

    if (a < 13) v += (13.0 - a) / sum * dp(a + 1, b, c, d, x, y);
    if (b < 13) v += (13.0 - b) / sum * dp(a, b + 1, c, d, x, y);
    if (c < 13) v += (13.0 - c) / sum * dp(a, b, c + 1, d, x, y);
    if (d < 13) v += (13.0 - d) / sum * dp(a, b, c, d + 1, x, y);
    if (x == 4) {
        double t = INF;
        for (int i = 0; i < 4; i++) t = min(t, 1.0 / sum * dp(a, b, c, d, i, y));
        v += t;
    }
    if (y == 4) {
        double t = INF;
        for (int i = 0; i < 4; i++) t = min(t, 1.0 / sum * dp(a, b, c, d, x, i));
        v += t;
    }

    return v;
}

int main() {
    cin >> A >> B >> C >> D;
    memset(f, -1, sizeof f);

    double  t = dp(0, 0, 0, 0, 4, 4);
    if (t > INF / 2) t = -1;

    printf("%.3lf\n", t);

    return 0;
}
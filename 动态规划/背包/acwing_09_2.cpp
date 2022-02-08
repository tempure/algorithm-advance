#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
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


//2022 2.9 update
//lyd 讲解，不用yxc那种递推消去式子观察的方法，这种直接理解更为简单
//https://www.acwing.com/video/1972/

//分组背包
//循环内外层顺序 外到内 阶段->状态->决策 具体参考蓝书
//时间复杂度O(N*M*S) N组数 M体积 S每组物品数量

const int N = 110;
int v[N], w[N], f[N];

void solve() {
    memset(f, 0xcf, sizeof f);
    f[0] = 0; //或者直接注释当前行和上一行，不初始化也能AC
    int n, m;
    cin >> n >> m; //m 体积
    for (int i = 0; i < n; i++) {
        int s; cin >> s; //该组物品数量
        for (int j = 0; j < s; j++) cin >> v[j] >> w[j]; //边读边求

        for (int j = m; j >= 0; j--)
            for (int k = 0; k < s; k++)
                if (v[k] <= j) f[j] = max(f[j], f[j - v[k]] + w[k]);
    }
    cout << f[m] << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
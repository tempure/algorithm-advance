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

//枚举法 状压DP 较慢 不如生成法
//https://www.acwing.com/activity/content/code/content/592418/
//https://www.acwing.com/video/1962/

int n, m;
ll f[12][1 << 11]; //第i行状态为j时，前i行的方案数
bool in_s[1 << 11]; //连续偶数个0的二进制所有的合法的数 标记预处理

void solve() {
    while (cin >> n >> m && n) {
        for (int i =  0; i < 1 << m; i++) { //预处理 in_s[] 这个位运算比较费解，之前写的最初的版本比较容易理解
            bool cnt = 0, has_odd = 0;
            for (int j = 0; j < m; j++)
                if (i >> j & 1) has_odd |= cnt, cnt = 0;
                else cnt ^= 1;
            in_s[i] = has_odd | cnt ? 0 : 1;
        }
        f[0][0] = 1;
        for (int i = 1; i <= n; i++) //行数从1开始
            for (int j = 0; j < 1 << m; j++) {
                f[i][j] = 0; //多样例
                for (int k = 0; k < 1 << m; k++)
                    if ((j & k) == 0 && in_s[j | k])
                        f[i][j] += f[i - 1][k];
            }
        cout << f[n][0] << endl; //最后一行不能有伸出来的，全为0
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
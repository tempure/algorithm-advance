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
const ll mod = 1000000000;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head


//CH5302 金字塔 区间DP写法
//复杂度均为 O(N^3)
//https://www.acwing.com/solution/content/49636/

/*
DP写法不要瞎初始化 memset(f, -1, sizeof f)
初始化之后即使在  else if (s[l] == s[r]){}里面加上 f[l][r] = 0,也还是不对，把len+=2 改为 len++, k+=2 -> k++还是不对
我暂且不知道为啥....
*/

const int N = 310;
ll f[N][N];
char s[N];

void solve() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    //DFS序长度一定为奇数，可以画一个三个点的树，然后观察加点，归纳可以证明
    if (n % 2 == 0) cout << 0 << endl;
    else {
        for (int len = 1; len <= n; len += 2) //len++也可以AC +2 直接保证奇偶性不变一直为可能有效区间
            for (int l = 1; l + len - 1 <= n; l ++) {
                int r = l + len - 1;
                if (len == 1) f[l][r] = 1;
                else if (s[l] == s[r]) { //子树DFS序首尾一定相同
                    for (int k = l + 2; k <= r; k ++)
                        if (s[k] == s[r])
                            f[l][r] = (f[l][r] + f[l + 1][k - 1] * f[k][r]) % mod;
                }
            }
        cout << f[1][n] << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
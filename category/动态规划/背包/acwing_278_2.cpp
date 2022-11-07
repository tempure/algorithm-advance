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

//01 背包变种，区别是只计算体积，物品价值都是0
//将原版的 max 改为求和

const int N = 1e4 + 10;
int f[N];

void solve() {
    int n, m;
    cin >> n >> m;
    f[0] = 1; //f[j], j 体积为0，不选也是一种方案
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v; //边循环边读，不用开个数组
        for (int j = m; j >= v; j--)  //逆序
            f[j] += f[j - v];
    }
    cout << f[m] << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
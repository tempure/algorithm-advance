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

//贪心，每棵子树，只加到其和父节点的那条边就行了
//需要满足的一个性质就是：对于每个子树，所有叶子节点到当前子树root距离肯定是相同的，不然到最高的root不相等了

const int N = 2050;
int n;
int w[N];
int ans;

int dfs(int u) {
    if (u * 2 > (1 << n + 1) - 1) return 0; //叶子节点
    int l = dfs(2 * u) + w[u * 2];
    int r = dfs(u * 2 + 1) + w[u * 2 + 1];
    ans += abs(l - r);
    return max(l, r);
}

void solve() {
    cin >> n;
    for (int i = 2; i <= (1 << n + 1) - 1; i++) cin >> w[i];
    dfs(1);
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
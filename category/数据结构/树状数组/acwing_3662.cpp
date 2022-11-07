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

/*
https://www.acwing.com/problem/content/description/1018/ 小数据版本 1e3 可以N^2 DP
元素w[i] 1e9 先离散化
n 范围1e5 不能直接N^2暴力DP
用树状数组优化优化查找前缀中最大元素的过程 总复杂度O(N*logN)
*/

/*
f[i]:以w[i]结尾的最大单调子序列和
以离散化之后的所有w[i]也就是元素权值为下标建立BIT
然后下标对应的元素值tr[i]就是f[i]
每次查对应下标前面的前缀，假设当前元素是i，所有小于w[i]的元素w[j],组成的上升子序列中，最大的f[i]是多少，更新即可

注意BIT的add操作和也可以改为max操作，来获取前缀中的最大值,边加边维护，动态过程
*/
const int N = 1e5 + 10;
int n;
int w[N];
ll tr[N];
vi xs;
ll f[N];

int get(int x) {
    return lower_bound(all(xs), x) - xs.begin() + 1; //离散化下标从1开始
}

int lowbit(int x) {
    return x & -x;
}

void add(int x, ll v) {
    for (int i = x ; i <= n; i += lowbit(i))
        tr[i] = max(tr[i], v);
}

ll query(int x) { //前缀x中的最大值
    ll res = 0;
    for (int i = x; i; i -= lowbit(i))
        res = max(res, tr[i]);
    return res;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        xs.push_back(w[i]);
    }
    sort(all(xs));
    xs.erase(unique(all(xs)), xs.end());

    ll res = 0;
    for (int i = 0; i < n; i++) {
        int k = get(w[i]);
        f[i] = query(k - 1) + w[i];
        res = max(res, f[i]);
        add(k, f[i]);
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}
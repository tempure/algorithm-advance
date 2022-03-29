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

//https://atcoder.jp/contests/abc175/editorial/72

/*
每个点出发的路径必然唯一而且是一个简单“完整”的环路径，不存在半路出现环前面路径是链。。。仔细想想可就行了
证明就是鸽巢原理的意思，你一直走肯定会循环的

那么直接枚举每个点开始的环路径，但是题目要求是走1到k次，不是必须走k步
那么对于每个环路径，可以枚举停留在环的哪里最后才能最大。。。。
*/

void solve() {
    int n, k;
    cin >> n >> k;
    vi p(n), c(n);
    for (int i = 0; i < n; i++) cin >> p[i], p[i]--; //下标0开始
    for (int i = 0; i < n; i++) cin >> c[i];

    ll ans = -2e9;
    for (int i = 0; i < n; i++) { //枚举每个点出发的环路径
        int v = i;
        ll cy_sum = 0; //环路径权值和
        ll cy_cnt = 0; //环长度

        while (1) {
            cy_cnt++;
            cy_sum += c[v];
            v = p[v];
            if (v == i)break;
        }

        ll path = 0; //开始到停留点的路径权值和
        int cnt = 0; //最后停留在哪里
        while (1) {
            cnt++;
            path += c[v];
            if (cnt > k) break;
            int num = (k - cnt) / cy_cnt; //还能走完整的环的数量
            ll score = path + max(0ll, cy_sum) * num;
            ans = max(ans, score);
            v = p[v];
            if (v == i)break;
        }
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
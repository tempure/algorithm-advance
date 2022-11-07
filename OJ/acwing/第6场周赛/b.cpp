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
1e9以内的所有由4，7构成位数的所有数，每位可选4，7，有2^1+2^2+...2^10个数 只有2000多个，直接先dfs预处理即可

然后每次询问区间，和预处理的区间[0,4][5,7][8,44][45,47]...每一个都求交集，然后答案加上交集长度*预处理区间的右端点元素值
*/

vector<ll> S; //全是4的10位数 会爆int

void dfs(int u, ll x) { //当前第u位放x
    S.push_back(x); //第一个区间开头从0开始
    if (u == 10) return; //最多枚举10位数
    dfs(u + 1, x * 10 + 4);
    dfs(u + 1, x * 10 + 7);
}


void solve() {
    dfs(0, 0);
    sort(all(S));

    ll l, r;
    cin >> l >> r;
    ll res = 0;
    for (int i = 1; i < sz(S); i++) { //枚举每一个预处理的相邻区间
        ll a = S[i - 1] + 1, b = S[i];
        //没有交集要和0取max 用这俩区间右端点较小的减去左端点较大的，适用于所有区间相交长度
        res += S[i] * max(0ll, (min(r, b) - max(l, a) + 1));
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
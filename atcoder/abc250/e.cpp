#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
mt19937_64 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
// head

//https://atcoder.jp/contests/abc250/submissions/31536215
//https://www.bilibili.com/video/BV19F411j7A3?t=2122.4
//https://atcoder.jp/contests/abc250/editorial/3933

//Zobrist Hash 直接前缀和比较

using u64 = unsigned long long;
const int N = 201000;
map<int, u64> cnt;
set<int> cnta, cntb;
u64 ha[N], hb[N];
int n, a[N], b[N], q;
int main() {
    scanf("%d", &n);
    rep(i, 1, n + 1) {
        scanf("%d", &a[i]);
        if (!cnt.count(a[i])) cnt[a[i]] = mrand();
        ha[i] = ha[i - 1];
        if (!cnta.count(a[i])) ha[i] += cnt[a[i]];
        cnta.insert(a[i]);
    }
    rep(i, 1, n + 1) {
        scanf("%d", &b[i]);
        if (!cnt.count(b[i])) cnt[b[i]] = mrand();
        hb[i] = hb[i - 1];
        if (!cntb.count(b[i])) hb[i] += cnt[b[i]];
        cntb.insert(b[i]);
    }
    scanf("%d", &q);
    rep(i, 0, q) {
        int x, y;
        scanf("%d%d", &x, &y);
        puts(ha[x] == hb[y] ? "Yes" : "No");
    }
}

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
#define endl '\n'
#define watch(x) cerr << (#x) << " is " << (x) << endl
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

//由于所有区间端点都是整数，那么直接开区间用+-0.5的方式来表示大小偏移

//直接暴力枚举所有区间的组合
//https://atcoder.jp/contests/abc207/editorial/2159
//Note that two intervals [a,b] and [c,d] intersects if and only if max(a,c)≤min(b,d).

void solve() {
    int N; cin >> N;
    vector<double> l(N), r(N);
    for (int i = 0; i < N; i++) {
        int t; cin >> t >> l[i] >> r[i];
        t--;
        if (t & 1) r[i] -= 0.5;
        if (t & 2) l[i] += 0.5;
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            ans += (max(l[i], l[j]) <= min(r[i], r[j]));
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
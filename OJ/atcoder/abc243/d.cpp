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

//https://atcoder.jp/contests/abc243/editorial/3555
//这玩意儿是 deque 根本不是栈啊（）这题解怎么搞得

void solve() {
    ll n, x;
    cin >> n >> x;
    string s;
    cin >> s;
    deque<char> stk;
    for (auto c : s)
        if (c == 'U' && !stk.empty() && (stk.back() == 'L' || stk.back() == 'R')) stk.pop_back();
        else stk.push_back(c);
    while (!stk.empty()) {
        auto t = stk.front();
        stk.pop_front();
        if (t == 'U') x /= 2;
        else if (t == 'L') x *= 2;
        else x = x * 2 + 1;
    }
    cout << x << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
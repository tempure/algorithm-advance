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

//https://atcoder.jp/contests/abc198/submissions/21669961
//https://atcoder.jp/contests/abc198/editorial/1082


// 10! == 3628800

void solve() {
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    map <char, int> mp;
    for (auto c : s1) mp[c]++;
    for (auto c : s2) mp[c]++;
    for (auto c : s3) mp[c]++;
    if (sz(mp) > 10) {
        puts("UNSOLVABLE");
        return;
    }
    string s0;
    for (auto p : mp) s0 += p.first;
    int m = sz(s0); //所有出现过的不同字母的总数
    vi v(10);
    for (int i = 0; i < 10; i++) v[i] = i; //next_permutation 初始

    auto val = [&](char c) {
        for (int i = 0; i < m; i++)
            if (c == s0[i]) return v[i];
        return -1;
    };
    do {
        if (val(s1[0]) == 0 || val(s2[0]) == 0 || val(s3[0]) == 0) {
            continue;
        }
        ll x1 = 0, x2 = 0, x3 = 0;
        for (auto c : s1) {
            x1 *= 10;
            x1 += val(c);
        }
        for (auto c : s2) {
            x2 *= 10;
            x2 += val(c);
        }
        for (auto c : s3) {
            x3 *= 10;
            x3 += val(c);
        }
        if (x1 + x2 == x3) {
            cout << x1 << endl;
            cout << x2 << endl;
            cout << x3 << endl;
            return;
        }
    } while (next_permutation(v.begin(), v.end()));
    cout << "UNSOLVABLE" << endl;
}


int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
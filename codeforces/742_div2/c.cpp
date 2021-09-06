#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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

//https://codeforces.com/blog/entry/94581

void solve() {
    string s, s1, s2;
    cin >> s;
    for (int i = 0; i < sz(s); i++) {
        if (i & 1) s2 += s[i];
        else s1 += s[i];
    }
    if (s2.empty()) {
        cout << stoi(s1) - 1 << endl; //positive
        return;
    }
    cout << (stoi(s1) + 1) * (stoi(s2) + 1) - 2 << endl; //positive
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
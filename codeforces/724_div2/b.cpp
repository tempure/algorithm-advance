#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
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

// tutorial :https://codeforces.com/blog/entry/91520

void solve() {
    int n; string s;
    cin >> n >> s;
    set<string> se;
    for (int i = 0; i < n; i++) {
        string ss; //s 的的所有子串
        for (int k = 0; k < 3 && i + k < n; k++) {
            ss.push_back(s[i + k]);
            se.insert(ss);
        }
    }

    for (int len = 1; len <= 3; len++) {
        string t(len, 'a');
        while (true) {
            if (se.count(t) == 0) {
                cout << t << endl;
                return;
            }
            int idx = len - 1; //从后往前字典序递增子串
            while (idx >= 0 && t[idx] == 'z') {
                t[idx] = 'a';
                idx--;
            }
            if (idx < 0) break;
            t[idx]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while (t --) solve();

    return 0;
}
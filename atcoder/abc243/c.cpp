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

void solve() {
    int n;
    cin >> n;
    map<int, vector<pii>> mp;
    for (int i = 0; i < n; i++) {
        int xi, yi;
        cin >> xi >> yi;
        mp[yi].pb({xi, i});
    }
    string s;
    cin >> s;
    for (auto t : mp) {
        bool flagl = false, flagr = false;
        auto a = t.se;
        sort(all(a));
        for (auto x : a) {
            if (s[x.se] == 'R') flagr = true;
            if (s[x.se] == 'L') {
                if (flagr) {
                    puts("Yes");
                    return;
                }
            }
        }
    }
    puts("No");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
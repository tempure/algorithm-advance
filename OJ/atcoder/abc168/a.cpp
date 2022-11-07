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

//这题意。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。

void solve() {
    string s;
    cin >> s;
    reverse(all(s));
    set<int> S1{2, 4, 5, 7, 9};
    set<int> S2{0, 1, 6, 8};
    set<int> S3{3};
    for (int i = 0; s[i]; i++) {
        if (S3.count(s[i] - '0')) {
            puts("bon");
            break;
        }
        else if (S2.count(s[i] - '0')) {
            puts("pon");
            break;
        }
        else {
            puts("hon");
            break;
        }
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
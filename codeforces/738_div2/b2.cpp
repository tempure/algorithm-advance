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

int get(string s) {
    int cnt = 0;
    for (int i = 0;  i < sz(s) - 1; i++)
        if (s[i] == s[i + 1]) cnt++;
    return cnt;
}

void solve() {
    int n;
    cin >> n;
    string ss;
    cin >> ss;
    string s = ss;
    int len = sz(s);
    if (s[0] == '?') s[0] = 'B';
    for (int i = 1; i < len; i++) {
        if (s[i] == '?') {
            if (s[i - 1] == 'B') s[i] = 'R';
            else s[i] = 'B';
        }
    }
    int ans = get(s);
    string s2 = ss;
    if (s2[0] == '?') s2[0] = 'R';
    for (int i = 1; i < len; i++) {
        if (s2[i] == '?') {
            if (s2[i - 1] == 'B') s2[i] = 'R';
            else s2[i] = 'B';
        }
    }
    if (ans < get(s2)) cout << s << endl;
    else cout << s2 << endl;
}
int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
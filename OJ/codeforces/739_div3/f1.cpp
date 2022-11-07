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

void solve() {
    unordered_set<int> s;
    string n;
    int k;
    cin >> n >> k;
    // cout << n << ' ' << k << endl;
    for (int i = 0; n[i]; i++) s.insert(n[i] - '0');
    if (sz(s) <= k) cout << n << endl;
    else {
        if (k == 1) cout << string(sz(n), n[0]) << endl;
        else {
            bool flag1 = false, flag2 = false;
            for (int i = 2; n[i]; i++) {
                if (n[i] > n[0]) flag1 = true;
                if (n[i] > n[1]) flag2 = true;
            }
            if (flag1 && flag2) {
                cout << (char)n[0];
                cout << (char)(n[1] + 1);
                cout << string(sz(n) - 2, (char)(n[0]));
                puts("");
            }
            else if (!flag2) {
                cout << (char)n[0];
                cout << string(sz(n) - 1, (char)(n[1] + 1));
                puts("");
            }
        }
    }
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
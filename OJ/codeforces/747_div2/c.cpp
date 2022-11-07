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
    int n;
    cin >> n;
    char c;
    cin >> c;
    string s;
    cin >> s;
    vi ans;
    bool flag = true;
    for (auto x : s) {
        if (x != c) {
            flag = false;
            break;
        }
    }
    if (!flag) {
        for (int i = 1; i <= n; i++) {
            flag = true;
            for (int j = i; j <= n; j++) {
                flag &= (s[j - 1] == c);
                j += i - 1; //make time comlexity O(S*log(S))
            }
            if (flag) {
                ans.pb(i);
                break;
            }
        }
        if (!flag) {
            ans.pb(n);
            ans.pb(n - 1);
        }
    }
    cout << sz(ans) << '\n';
    for (auto x : ans) {
        cout << x << ' ';
    }
    if (sz(ans))cout << '\n';
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
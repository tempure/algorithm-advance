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

//multiset erase
//https://www.cplusplus.com/reference/set/multiset/erase/#:~:text=Value%20to%20be%20removed%20from%20the%20multiset.%20All%20elements%20with%20a%20value%20equivalent%20to%20this%20are%20removed%20from%20the%20container.
void solve() {
    int n, m;
    cin >> n >> m;
    multiset<int> S;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        S.insert(x);
    }
    for (int i = 0 ; i < m; i++) {
        int x;
        cin >> x;
        if (S.count(x)) {
            S.erase(x);
        }
        else {
            puts("No");
            return;
        }
    }
    puts("Yes");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
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
#define watch(x) cerr << (#x) << " is " << (x) << endl
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
    int n, m;
    cin >> n >> m;
    vi v(n + 10, 0);
    // set<pii> S;
    for (int i = 0 ; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (v[a] > 2 || v[b] > 2) {
            puts("No");
            return;
        }
        // if (a == b) {
        //     puts("No");
        //     return;
        // }
        // if (S.count({a, b}) || S.count({b, a})) continue;
        v[a] ++ , v[b] ++;
        // S.insert({a, b});
    }
    // for(auto t : v){
    //     cout << t << ' ';

    // }
    // puts("");
    for (auto t : v) {
        if (t > 2) {
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
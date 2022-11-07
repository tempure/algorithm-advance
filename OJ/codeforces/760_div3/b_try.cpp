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
    int n;
    cin >> n;
    if(n == 3){
        string s;
        cin >> s;
        cout << s << s[0] << endl;
        return;
    }
    vector<string> v(n - 2);
    vector<char> res;
    cin >> v[0];
    res.pb(v[0][0]);
    res.pb(v[0][1]);
    for (int i = 1; i < n - 2; i++) {
        cin >> v[i];
        if (i == n - 3) {
            res.pb(v[i][0]);
            res.pb(v[i][1]);
            continue;
        }
        if (v[i][0] != v[i - 1][1]) {
            // res.pb(v[i - 1][1]);
            res.pb(v[i][0]);
            // if (i == n - 1) res.pb(v[i][1]);
        }
        else {
            res.pb(v[i][1]);
        }
    }
    for (auto t : res) cout << t;
    puts("");
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
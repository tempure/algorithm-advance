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

const int N = 110;
int a[N];

void solve() {
    int n;
    cin >> n;
    int res = 1;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if(a[0] == 1) res ++;
    for (int i = 1; i < n; i++) {
        if (a[i - 1] == 1 && a[i] == 1) res += 5;
        if (a[i] == 0 && a[i - 1] == 0) {
            cout << - 1 << endl;
            return;
        }
        if (a[i] == 1 && a[i - 1] == 0) res += 1;
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
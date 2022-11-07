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

// this is a so fucking problem WA 10 times lol

int a[1010];
int n;

bool check() {
    // for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    // cout << endl;
    for (int i = 1; i <= n; i++) {
        if (a[i] != i) return false;
    }
    return true;
}

void solve() {
    memset(a, 0, sizeof a);
    cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++)cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (check()) {
            cout << cnt << endl;
            return;
        }
        // bool flag = false;
        for (int j = (i % 2 == 0 ? 2 : 1); j + 1 <= n ; j += 2) {
            if (a[j] > a[j + 1]) {
                // flag = true;
                swap(a[j], a[j + 1]);
            }
        }
        cnt++;
        // if (flag) cnt++;
        if (check()) {
            cout << cnt << endl;
            return;
        }
    }
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
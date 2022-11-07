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

const int N = 1e5 + 10;
int a[N];
ll s[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    if (s[n] % 3) {
        cout << 0 << endl;
        return;
    }
    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; i++)
        if (s[i] == s[n] / 3)
            cnt1++;

    for (int i = n; i >= 1; i--) {
        if (s[n] - s[i] == s[n] / 3)
            cnt2++;
    }
    if(cnt1 + cnt2)
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
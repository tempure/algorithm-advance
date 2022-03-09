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

int n, d;

int cnt(vector<int> &schedule) {
    int mx = 0, mn = 1e9;
    for (int i = 1; i < n; ++i) {
        mx = max(mx, schedule[i] - schedule[i - 1] - 1);
        mn = min(mn, schedule[i] - schedule[i - 1] - 1);
    }
    return min(mn, max(d - schedule.back() - 1, (mx - 1) / 2));
}

void solve() {
    cin >> n >> d;
    vector<int> a(n + 1);
    int mn = d, min_pos = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] - a[i - 1] - 1 < mn) {
            mn = a[i] - a[i - 1] - 1;
            min_pos = i;
        }
    }
    vector<int> schedule;
    for (int i = 0; i <= n; ++i) {
        if (i != min_pos) {
            schedule.push_back(a[i]);
        }
    }
    int ans = cnt(schedule);
    if (min_pos > 1) {
        schedule[min_pos - 1] = a[min_pos];
    }
    ans = max(ans, cnt(schedule));
    cout << ans << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
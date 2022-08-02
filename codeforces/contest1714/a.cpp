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

void solve() {
    int n, h, m;
    vector<pii> ala;
    cin >> n >> h >> m;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        ala.pb({x, y });
    }
    sort(all(ala));
    for (int i = 0; i < n; i++) {
        if (ala[i].first >= h) {
            int x = ala[i].first, y = ala[i].second;
            if (x == h && y >= m) {
                cout << 0 << ' ' << y - m << endl;
                return;
            }
            else if (x > h) {
                int rest = x * 60 + y - (h * 60 + m);
                cout << rest / 60 << ' ' << rest % 60 << endl;
                return;
            }
        }
    }
    int x = ala[0].first, y = ala[0].second;
    int ress = (x + 24) * 60 + y - (h * 60 + m);
    cout << ress / 60 << ' ' << ress % 60 << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
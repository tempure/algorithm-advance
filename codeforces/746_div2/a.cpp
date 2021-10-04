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

const int N = 1e3 + 10;
int a[N];

void solve() {
    int n, h;
    cin >> n >> h;
    int max1 = -1, max2 = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        // if (i == 0) {
        //     max1 = a[i];
        //     continue;
        // }
        if (a[i] > max1) {
            max2 = max1;
            max1 = a[i];
        }
        else if (a[i] > max2) max2 = a[i];
    }
    // int cnt = 0;
    if (h % (max1 + max2) == 0) {
        cout << h / (max1 + max2) * 2 << endl;
        return;
    }
    int res;
    if (h > max1 + max2) {
        // int cnt = a[i] / (max1 + max2);
        // a[i] %= (max1 + max2);
        // if(a[i] > max1) cnt++;
        res = h / (max1 + max2) * 2;
        h %= (max1 + max2);
        if (h > max1) {
            res += 2;
        }
        else res += 1;
    }
    else if (h == max1 + max2) res = 2;
    else {
        if (h > max1) {
            res = 2;
        }
        else res = 1;
    }
    cout << res << endl;
    // cout << max1 << ' ' << max2 << endl;

}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
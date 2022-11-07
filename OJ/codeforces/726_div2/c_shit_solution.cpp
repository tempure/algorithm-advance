#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
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

const int N = 2e5 + 10;
int a[N];
// um<int, int> m;

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    if (n == 4) {
        if (a[0] == a[1])
            cout << a[0] << ' ' << a[2] << ' ' << a[3] << ' ' << a[1] << endl;
        else if (a[2] == a[3])
            cout << a[2] << a[0] << ' ' << a[1] << ' ' << a[3] << endl;
        else cout << a[1] << ' ' << a[3] << ' ' << a[0] << ' ' << a[2] << endl;
    }
    else {
        if (a[0] == a[1]) {
            cout << a[0] << ' ';
            for (int i = 2; i < n; i++) cout << a[i] << ' ';
            cout << a[1] << endl;
        }
        else if (a[n - 2] == a[n - 1]) {
            cout << a[n - 2] << ' ';
            for (int i = 0; i < n - 2; i++) cout << a[i] << ' ';
            cout << a[n - 1] << endl;;
        }
        else {
            int m = 0;
            int mx = 0x3f3f3f3f;
            for (int i = 0; i < n - 1; i++)
                if (a[i + 1] - a[i] < mx) {
                    mx = a[i + 1] - a[i];
                    m = i;
                }
            cout << a[m] << ' ';
            for (int i = 0; i < n; i++) {
                if (i == m || i == m + 1) continue;
                cout << a[i] << ' ';
            }
            cout << a[m + 1] << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}
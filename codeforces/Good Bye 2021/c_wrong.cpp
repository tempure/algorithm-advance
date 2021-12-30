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

const int N = 100;
int a[N];

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    if (n == 2) {
        int a, b;
        cin >> a >> b;
        if (abs(a - b) == 1) {
            cout << 0 << endl;
            return;
        }
    }
    for (int i = 1; i <= n; i++) cin >> a[i];
    int cnt = 0;
    // sort(a + 1, a + n + 1);
    int maxseg = 0;
    for (int i = 2; i <= n; i++) {
        cnt = 0;
        bool flag = false;
        if (a[i] == a[i - 1] + 1) {
            while (a[i] == a[i - 1] + 1) {
                if (i > n) break;
                i++;
                flag = true;
                cnt++;
            }
        }
        if (flag)i--;
        maxseg = max(maxseg, cnt);
    }
    cout << n - (maxseg + 1) << endl;
    // for(int i = 1; i<=n; i++) cout << a[i] << ' ';
    // cout << endl;
    // cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
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


const int N = 820;
int a[N][N];
// int tmp[N * N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];

    int res = 0x3f3f3f3f;
    multiset<int> m;
    for (int i = 1; i + k - 1 <= n; i++)
        for (int j = 1; j + k - 1 <= n; j++) {
            // int cnt = 0;
            m.clear();
            for (int ii = i; ii <= i + k - 1; ii++)
                for (int jj = j; jj <= j + k - 1; jj++) {
                    // tmp[++cnt] = a[ii][jj];
                    m.insert(a[ii][jj]);
                }
            // for (int i = 1; i <= cnt; i++) cout << tmp[i] << ' ';
            // cout << endl;
            // cout << endl;
            // sort(tmp + 1, tmp + cnt + 1);
            auto t = m.begin();
            // res = min(res, tmp[(cnt + 1) / 2]);
        }


    cout << res << endl;
    return 0;
}

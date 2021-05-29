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


int v[5] = {0, 11, 111, 1111, 11111};
int f[12000];

//打表+完全背包

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while (t --) {
        memset(f, 0, sizeof f);
        int n; cin >> n;
        if (n > 5000) {
            puts("YES");
            continue;
        }
        for (int i = 1; i <= 4; i++) f[v[i]] = 1;
        // f[11] = 1;

        for (int i = 1; i <= 4; i++)
            for (int j = v[i]; j <= n; j++)
                f[j] = f[j] + f[j - v[i]];

        // for (int i = 1; i <= n; i++) cout << f[i] << ' ';
        // puts("");

        if (f[n]) puts("YES");
        else puts("NO");
    }

    return 0;
}
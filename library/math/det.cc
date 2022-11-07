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


//行列式模板 NxN矩阵

ll a[20][20];

ll det(int n) {
    ll ans = 1;
    int sign = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x = i, y = j;
            while (a[y][i]) {
                ll t = a[x][i] / a[y][i];
                for (int k = i; k < n; k++)
                    a[x][k] = a[x][k] - a[y][k] * t;
                swap(x, y);
            }
            if (x != i) {
                for (int k = 0; k < n; k++)swap(a[i][k], a[x][k]);
                sign ^= 1;
            }
        }
        if (a[i][i] == 0)
            return 0;
        else
            ans = ans * a[i][i];
    }
    if (sign)ans *= -1;
    return ans;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    cout << det(n) << endl;
    return 0;
}

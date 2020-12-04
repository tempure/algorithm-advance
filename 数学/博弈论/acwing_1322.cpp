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
//snippet-head


const int N = 1010;
int n;
int a[N], l[N][N], r[N][N];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

        for (int len = 1; len <= n; len ++) //区间长度
            for (int i = 1; i + len - 1 <= n; i++) { //左端点
                int j = i + len - 1;
                if (len == 1) l[i][j] = r[i][j] = a[i];
                else {
                    int L = l[i][j - 1], R = r[i][j - 1], X = a[j];
                    if (R == X) l[i][j] = 0;
                    else if (X < L && X < R ||  X > L && X > R) l[i][j] = X;
                    else if (L > R) l[i][j] = X - 1;
                    else l[i][j] = X + 1;

                    L = l[i + 1][j], R = r[i + 1][j], X = a[i];
                    if (L == X) r[i][j] = 0;
                    else if (X < L && X < R || X > L && X > R) r[i][j] = X;
                    else if (R > X) r[i][j] = X - 1;
                    else r[i][j] = X + 1;
                }
            }
        if (n == 1) puts("1");
        else printf("%d\n", l[2][n] != a[1]);
    }
    return 0;
}
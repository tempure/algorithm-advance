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


//中国剩余定理模板

const int N = 11;

int n;
int A[N], B[N];

void exgcd(ll a, ll b, ll &x, ll & y) {
    if (!b)
        x = 1, y = 0;
    else {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}


int main() {
    scanf("%d", &n);
    ll M = 1;

    //方程组为 x 同余 B[i] mod (A[i])
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &A[i], &B[i]);
        M *= A[i];
    }

    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll Mi = M / A[i];
        //求Mi*ti 同余 1(mod mi) 的ti
        ll ti, x;
        exgcd(Mi, A[i], ti, x);
        res += (B[i] * Mi * ti);
    }

    //中国剩余定理给出的通解是 x + k * M 对M取模即可得到最小正整数解
    cout << (res % M + M )  % M << endl;
}

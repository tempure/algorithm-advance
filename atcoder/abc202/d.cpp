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


//editorial：https://atcoder.jp/contests/abc202/editorial/1893

const int N = 30;
ll dp[N + 1][N + 1];

string find(int a, int b, ll k) {
    if (a == 0) return string(b, 'b'); //一个string,b个 'b'
    if (b == 0) return string(a, 'a');

    //当前层dp是a个'a',b个'b'，多一个b就要少一个a，当前字符串排序大于k就加'a'，反之加'b'
    if (k <= dp[a - 1][b]) return string("a") + find(a - 1, b, k);
    else return string("b") + find(a, b - 1, k - dp[a - 1][b]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int a, b;
    ll k;
    cin >> a >> b >> k;

    //组合数dp[i][j]意思是从长i宽j的方格，走到(i,j)的走法数量
    //本质是：C(i+j,j) = C(i+j-1,j) + C(i+j-1, j-1)
    //dp[i][j] -> C(i + j, j)
    dp[0][0] = 1;

    for (int i = 0; i <= a; i++)
        for (int j = 0; j <= b; j++) {
            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (j > 0) dp[i][j] += dp[i][j - 1];
        }
    cout << find(a, b, k) << endl;

    return 0;
}
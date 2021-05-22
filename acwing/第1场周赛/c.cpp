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


const int N = 1e6 + 10;
int a[N];
int dp[4][N];

int main_fun(int arr[], int n) {

    // dp[i][j] be the longest
    // subsequence of a[0...i]
    // with first j parts
    // int dp[4][n];
    // memset(dp, 0, sizeof(dp[0][0] * 4 * n));

    if (arr[0] == 0)
        dp[0][0] = 1;
    else
        dp[1][0] = 1;

    // Maximum length sub-sequence
    // of (0..)
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == 0)
            dp[0][i] = dp[0][i - 1] + 1;
        else
            dp[0][i] = dp[0][i - 1];
    }

    // Maximum length sub-sequence
    // of (0..1..)
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == 1)
            dp[1][i] = max(dp[1][i - 1] + 1,
                           dp[0][i - 1] + 1);
        else
            dp[1][i] = dp[1][i - 1];
    }

    // Maximum length sub-sequence
    // of (0..1..0..)
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == 0)
        {
            dp[2][i] = max(dp[2][i - 1] + 1,
                           max(dp[1][i - 1] + 1,
                               dp[0][i - 1] + 1));
        }
        else
            dp[2][i] = dp[2][i - 1];
    }

    // Maximum length sub-sequence
    // of (0..1..0..1..)
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == 1)
        {
            dp[3][i] = max(dp[3][i - 1] + 1,
                           max(dp[2][i - 1] + 1,
                               max(dp[1][i - 1] + 1,
                                   dp[0][i - 1] + 1)));
        }
        else
            dp[3][i] = dp[3][i - 1];
    }

    // Find the max length subsequence
    int ans = max(dp[2][n - 1], max(dp[1][n - 1],
                                    max(dp[0][n - 1], dp[3][n - 1])));

    // Print the answer
    // cout << (ans);

    return ans;
}

// Driver Code
int main() {

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int c; cin >> c;
        if (c == 1) a[i] = 0;
        else a[i] = 1;
    }
    cout <<  main_fun(a, n) << endl;
    return 0;
}
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

const int N = 2010;
const int INF = 0x3f3f3f3f;
int f[N][N];
int dp[N][N];
int n, m;

void print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			cout << dp[i][j] << ' ';
		cout << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c; cin >> c;
			if (c == '+') f[i][j] = 1;
			else f[i][j] = -1;
		}

	for (int i = n; i >= 1; i--)
		for (int j = m; j >= 1; j--) {
			if (i == n && j == m) dp[i][j] = 0;
			else if ((i + j) & 1) {
				dp[i][j] = INF;
				if (i + 1 <= n) dp[i][j] = min(dp[i][j], dp[i + 1][j] - f[i + 1][j]);
				if (j + 1 <= m) dp[i][j] = min(dp[i][j], dp[i][j + 1] - f[i][j + 1]);
			}
			else {
				dp[i][j] = -INF;
				if (i + 1 <= n) dp[i][j] = max(dp[i][j], dp[i + 1][j] + f[i + 1][j]);
				if (j + 1 <= m) dp[i][j] = max(dp[i][j], dp[i][j + 1] + f[i][j + 1]);
			}
		}
	// print();

	// cout << "******* " <<  dp[1][1] << endl;

	if (dp[1][1] == 0) puts("Draw");
	else if (dp[1][1] > 0) puts("Takahashi");
	else puts("Aoki");

	return 0;
}
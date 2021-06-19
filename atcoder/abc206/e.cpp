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

const int N = 1000010;
int v[N];

void primes(int n) {
  int cnt = 0;
  memset(v, 0, sizeof v);
  for (int i = 2; i <= n; i++) {
    if (v[i]) continue; //没有被筛过 那就是质数
    // cnt ++;
    for (int j = i; j <= n / i; j++) v[i * j] = 1; //对于每个数x 从x^2 开始筛，因为小于x^2的x的倍数已经被标记过了
  }

  // return cnt;
}

void solve() {
  int l, r;
  cin >> l >> r;
  ll res = 0;
  int cnt = 0;
  primes(r);
  for (int i = r / 2 + 1; i <= r; i++) {
    if (v[i] == 1) cnt++;
  }
  cout << 1ll * cnt * (cnt - 1) << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;
  while (t --) solve();

  return 0;
}
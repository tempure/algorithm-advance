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

const int N = 1e5; // 数组开sqrt(N) 的数量级即可 看循环的次数
int p1[N], c1[N]; //p存储质因子 c存储幂次
int p2[N], c2[N];

void divide(int n, int p[], int c[], int &m) {
    m = 0;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            p[++m] = i; c[m] = 0; //一定要先存i 然后c[m]=0 顺序反会错
            while (n % i == 0) n /= i, c[m]++;
        }
    }

    //n为质数直接存 上边的for循环不会进入
    if (n > 1) p[++m] = n, c[m] = 1;

    // //输出因子和对应次幂
    // for (int i = 1; i <= m; i++)
    //     cout << p[i] << ' ' << c[i] << endl;
    // cout << endl;
}


void solve() {
    int a, b, k;
    cin >> a >> b >> k;
    int m1 = 0, m2 = 0;
    divide(a, p1, c1, m1); divide(b, p2, c2, m2);
    int res = max(m1, m2) - min(m1, m2);
    int mm = min(m1, m2);
    for (int i = 1; i <= mm; i++)
        if (p1[i] != p2[i])res += 2;
        else if (c1[i] != c2[i]) res ++;

    if (res != k) cout << "NO" << endl;
    else cout << "YES" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}
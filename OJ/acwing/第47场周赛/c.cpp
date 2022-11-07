#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define endl '\n'
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

//https://www.acwing.com/video/3825/

//式子移项一下
// a[i] - a[i-1] = X[(i-1])%K] ->
// x0 = a[1]
// x1 = a[2]-a[1]
// x2 = a[3] - a[2]
// x0 = a[4] - a[3] = a[1], 此时k = 3合法
//看 a[i] - a[i-1] 的循环节 枚举循环节的长度


const int N = 1010;
int n;
int a[N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];

    vector<int> res;
    for (int k = 1; k <= n; k ++ ) {
        bool is_match = true;
        for (int i = k + 1; i <= n; i ++ ) //直接枚举第二个循环节开始的一项
            if (a[i] - a[i - 1] != a[i - k] - a[i - 1 - k]) {
                is_match = false;
                break;
            }

        if (is_match) res.push_back(k);
    }

    cout << res.size() << endl;
    for (auto k : res)
        cout << k << ' ';
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
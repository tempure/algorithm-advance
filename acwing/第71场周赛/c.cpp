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

//复杂度是 O(N*log(T))的
//做法是非常暴力的，就是一直模拟就行了
//但是复杂度证明需要稍微思考一下：https://www.acwing.com/solution/content/138256/

const int N = 2e5 + 10;
int n;
ll T;
int w[N];

void solve() {
    cin >> n >> T;
    for (int i = 0; i < n; i++) cin >> w[i];
    ll res = 0;
    while (true) {
        ll cnt = 0, sum = 0;
        for (int i = 0; i < n; i++)
            if (sum + w[i] <= T) {
                sum += w[i];
                cnt++;
            }
        if (!sum) break;
        res += T / sum * cnt;
        T %= sum;
    }

    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
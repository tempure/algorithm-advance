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

//https://blog.csdn.net/ydsrwex/article/details/114528520

const int N = 2e6;
int a[N];
int num[N]; //count

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int head = 1, tail = k;
    for (int i = 1; i <= k; i++) num[a[i]]++;
    int ans = 0x3f3f3f3f;
    for (int i = 0;; i++)
        if (num[i] == 0) {
            ans = i;
            break;
        }
    if (ans == 0) {
        cout << 0 << endl;
        return;
    }
    while (tail < n) {
        num[a[++tail]]++; //back pointer
        num[a[head]]--; //front pointer

        //当前没出现过的最小值若比之前没出现过的最小值小，则当前没出现过的最小值之前一定是在队中
        if (num[a[head]] == 0) ans = min(ans, a[head]);
        head++;
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
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

/*
枚举2个b的位置即可
其实就是求(n+1)*n/2和k的关系，第一个b往前移动一到i，第二个就会有n-i个选择
*/

const int N = 1e5 + 10;
ll sum[N];

// void init() {
//     int cnt = 1;
//     for (int i = 1; i < N; i++)sum[i] = i;
//     for (int i = 1; i < N; i++) sum[i] += sum[i - 1];
// }

void solve() {
    ll n, k;
    cin >> n >> k;

    for (int i = n - 1; i; i--) {
        if (k > n - i) k -= n - i;
        else {
            string s(n, 'a');
            s[i - 1] = s[n - k] = 'b';
            cout << s << endl;
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // init();
    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}
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

const int N = 1e5 + 10;
ll a[N];
map<ll, ll> mp;

int main() {
    int T = 1;
    cin >> T;
    while (T --) {
        mp.clear();
        ll n , ans = 0;
        cin >> n ;
        for (int i = 1 ; i <= n ; i ++) cin >> a[i];
        for (int i = 1 ; i <= n ; i ++) {
            ans += mp[a[i]] * (n - i + 1);
            mp[a[i]] += i;
        }
        cout << ans << '\n';
    }
    return 0;
}
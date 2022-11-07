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

const int N = 2e5 + 10;
int a[N];
multiset<int, greater<int> > ms;


void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    ll cnt = 0, cur = 0, ans = 0;

    for (int i = 1; i <= n; i++) {
        if (a[i] >= 0) cnt ++, cur += a[i]; //正的直接吃
        else {
            if (cur + a[i] >= 0) {
                cnt ++;
                cur += a[i];
                ms.insert(-a[i]); //set只放负的，用于反悔
            }
            else { //吃不下当前了，直接反悔尝试能不能吃
                if (ms.size() && *ms.begin() >= -a[i]) {
                    cur += *ms.begin(); //反悔到没吃前的血量
                    ms.erase(ms.begin());
                    cnt --;
                }
                if (cur + a[i] >= 0) cnt++, cur += a[i], ms.insert(-a[i]);
            }
        }
        ans = max(ans, cnt);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) {
        solve();
    }

    return 0;
}
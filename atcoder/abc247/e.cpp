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

int N, X, Y;

//滑动窗口
//https://atcoder.jp/contests/abc247/editorial/3776

ll calc(vector<int> & B) {
    ll i = 0, j = 0, cntX = 0, cntY = 0, res = 0; //必须开ll 会爆 int
    while (i != sz(B)) {
        while (j != sz(B) && (cntX == 0 || cntY == 0)) {
            if (B[j] == X) cntX ++;
            if (B[j] == Y) cntY ++;
            j += 1;
        }
        if (cntX > 0 && cntY > 0) res += sz(B) - j + 1;
        if (B[i] == X) cntX -= 1;
        if (B[i] == Y) cntY -= 1;
        i += 1;
    }
    return res;
}

void solve() {
    int i = 0;
    ll ans = 0;
    cin >> N >> X >> Y;
    vi a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    while (i != N) {
        vi B;
        while (i != N && a[i] >= Y && a[i] <= X) {
            B.pb(a[i]);
            i += 1;
        }
        if (sz(B) != 0) ans += calc(B);
        else i += 1;
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
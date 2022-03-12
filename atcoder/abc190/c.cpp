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

//https://atcoder.jp/contests/abc190/editorial/693

void solve() {
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> cond(M);
    for (auto& [A, B] : cond) cin >> A >> B;
    int K;
    cin >> K;
    vector<pair<int, int>> choice(K);
    for (auto& [C, D] : choice) cin >> C >> D;

    int ans = 0;
    for (int bit = 0; bit < 1 << K; bit++) {
        vector<bool> ball(N);
        for (int i = 0; i < K; i++) {
            const auto [C, D] = choice[i];
            ball[bit & (1 << i) ? C : D] = 1;
        }
        int cnt = 0;
        for (auto [A, B] : cond) if (ball[A] && ball[B]) cnt++;
        if (ans < cnt) ans = cnt;
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
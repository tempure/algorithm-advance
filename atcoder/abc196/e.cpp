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


//https://blog.csdn.net/justidle/article/details/115043200
//https://atcoder.jp/contests/abc196/editorial/953

//Can't understand math well...

const ll INF = numeric_limits<ll>::max() / 4;
void chmin(ll& a, ll b) { if (a > b) a = b; }
void chmax(ll& a, ll b) { if (a < b) a = b; }

int main() {
    ll N;
    cin >> N;
    ll low = -INF, high = INF, add = 0;
    for (ll i = 0; i < N; i++) {
        ll A, T;
        cin >> A >> T;
        if (T == 1) {
            low += A;
            high += A;
            add += A;
        }
        else if (T == 2) {
            chmax(low, A);
            chmax(high, A);
        }
        else {
            chmin(low, A);
            chmin(high, A);
        }
    }
    ll Q;
    cin >> Q;
    for (ll i = 0; i < Q; i++) {
        ll x;
        cin >> x;
        cout << clamp(x + add, low, high) << '\n';
    }
}

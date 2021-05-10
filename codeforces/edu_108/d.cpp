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



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<ll> A(N), B(N);

    for (auto &a : A) cin >> a;
    for (auto &b : B) cin >> b;

    ll total = 0;
    for (int i = 0; i < N; i++)
        total += A[i] * B[i];

    ll best = total;

    for (int center = 0; center < N; center++) {
        ll current = total;
        for (int x = center - 1, y = center + 1; x >= 0 && y < N; x--, y++) {
            current -= A[x] * B[x] + A[y] * B[y];
            current += A[x] * B[y] + A[y] * B[x];
            best = max(best, current);
        }
    }

    for (int between = 0; between < N; between++) {
        ll current = total;
        for (int x = between, y = between + 1; x >= 0 && y < N; x--, y++) {
            current -= A[x] * B[x] + A[y] * B[y];
            current += A[x] * B[y] + A[y] * B[x];
            best = max(best, current);
        }
    }

    cout << best << endl;

    return 0;
}
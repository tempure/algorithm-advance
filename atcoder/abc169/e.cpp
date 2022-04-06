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

//https://atcoder.jp/contests/abc169/submissions/13789675
//https://img.atcoder.jp/abc169/editorial.pdf

//这个题证明好迷啊。。。。。。。。。。。
//why  Considered that the median of X can
//be increased from A to B by repeating the operation of increasing one of the elements of X by 1

#define F0R(i, a) for (int i=0; i<(a); i++)

void solve() {
    int N; cin >> N;
    vi A(N), B(N); F0R(i, N) cin >> A[i] >> B[i];
    sort(all(A));
    sort(all(B));
    ll X, Y;
    if (N % 2 == 1) {
        X = A[N / 2];
        Y = B[N / 2];
    } else {
        X = A[N / 2 - 1] + A[N / 2];
        Y = B[N / 2 - 1] + B[N / 2];
    }

    cout << Y - X + 1 << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
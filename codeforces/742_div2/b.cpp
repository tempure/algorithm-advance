#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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

const int N = 3e5 + 10;
ll sum[N];
// unordered_set<ll> s;

void init() {
    for (int i = 1; i < N; i++) {
        sum[i] = sum[i - 1] ^ i;
        // s.insert(sum[i]);
    }
    // for(int i =0; i< 3; i++){
    //     cout <<"****" << i <<  ' ' << sum[i] <<  endl;
    // }
    // cout << (1 ^ 2) << endl;
}

void solve() {
    int a, b;
    ll res = 0;
    cin >> a >> b;
    if((sum[a-1] ^ a) == b) {
        res = a + 2;
        // cout << "**********1 ";
    }
    else if(a == b && sum[a - 1] == 0) res = a + 2;
    else if (sum[a - 1] == b) res = a;
    else res = a + 1;
    cout << res << endl;
}

int main() {
    init();
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
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

priority_queue<ll> pq;

int main() {
    int n, k1, k2, k;
    cin >> n >> k1 >> k2;
    k = k1 + k2;
    vector<ll> a(n), b(n), arr(n);
    for (int i = 0 ; i < n ; ++i)
        cin >> a[i];
    for (int i = 0 ; i < n ; ++i) {
        cin >> b[i];
        arr[i] = abs(a[i] - b[i]);
        pq.push(arr[i]);
    }
    while (k > 0) {
        ll curr = pq.top();
        pq.pop();
        pq.push(abs(curr - 1));
        k--;
    }
    ll ans = 0;
    while (!pq.empty()) {
        ll curr = pq.top();
        ans += (curr * curr);
        pq.pop();
    }
    cout << ans;
}
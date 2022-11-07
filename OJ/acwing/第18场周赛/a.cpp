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
const int N  = 110;
int a[N];
int cnt[N];

void solve() {
    int n, k;
    set<int> S;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        S.insert(a[i]);
        cnt[a[i]]++;
    }
    if (S.size() < k) {
        puts("NO");
        return;
    }
    puts("YES");
    int num = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[a[i]] > 0) {
            num++ ;
            cout << i << ' ';
            cnt[a[i]] = 0;
            if (num == k) {
                return;
            }
        }
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
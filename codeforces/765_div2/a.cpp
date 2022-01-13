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

//https://www.bilibili.com/video/BV1xR4y1g7xE

void solve() {
    int n, l;
    cin >> n >> l;
    int save[31] = {0};
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int cnt = 0;
        while (x) {
            save[cnt] += x % 2;
            x >>= 1;
            cnt++;
        }
    }
    int res = 0;
    for (int i = l - 1; i >= 0 ; i --) {
        res <<= 1;
        if (save[i] * 2 >= n) res++;
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
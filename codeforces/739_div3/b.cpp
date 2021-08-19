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

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    if (b - a == 1 || a - b == 1) {
        if (c == a) cout << b << endl;
        else if (c == b) cout << a << endl;
        else cout << -1 << endl;
        return;
    }

    if (a > b) swap(a, b);
    int p1 = b - (a - 1);
    int sum = (p1 - 1) * 2;
    if (c > sum) {
        cout << -1 << endl;
        return;
    }
    if(2 * a > b){
        cout << -1 << endl;
        return ;
    }
    // if(c > sum / 2) c = c%(sum /2);
    int res = ((c - 1) + p1);
    if (res > sum) res -= sum;
    // cout << "p1 = " << p1 << endl;
    // cout << "sum = " << sum << endl;
    if (res < 0) cout << -1 << endl;
    else cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
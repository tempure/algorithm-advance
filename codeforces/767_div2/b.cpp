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

bool is_prime(int x) {
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0 )return false;
    }
    return true;
}

void solve() {
    int l, r, k;
    cin >> l >> r >> k;
    if (l == r && l > 1) {
        puts("YES");
        return;
    }
    if (k == 0 && l == r) {
        if (l == 1) {
            puts("NO");
            return;
        }
        puts("YES");
        return;
    }
    int cnt;
    if((l & 1) && (r & 1)){
        cnt = (r - l) / 2 + 1; //3 4 5 6 7
    }
    else if((l & 1) && !(r & 1) || ((r & 1) && !(l & 1))){
        cnt = (r - l + 1) / 2; //3 6 .. 3, 5 
    }
    // 4, 6
    else cnt = (r - l) / 2; 
    // 4, 7
    if(cnt > k) puts("NO");
    else puts("YES");

    // l -= l - 1;
    // r -= l - 1;
    // l /= gcd(l, r);
    // r /= gcd(l, r);

    // l /= gcd(l, r);
    // r /= gcd(l, r);
    // if((l + r) / 2 > k) puts("NO");
    // else puts("YES");
    // int cnt = 0;
    // for (int i = l; i <= r; i++) {
    //     if (is_prime(i)) cnt++;
    // }
    // // if (l == 1) cnt++;
    // cout << cnt << ' ';
    // if (cnt > k) puts("NO");
    // else puts("YES");
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
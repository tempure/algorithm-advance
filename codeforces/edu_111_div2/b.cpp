#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
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


void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    int len = s.length();

    if (b >= 0) {
        cout << a * len + len * b << endl;
    }
    else {
        int cnt1 = 0;
        int c1 = 0, c0 = 0;
        int cnt0 = 0;
        int i = 0;
        while (i < len) {
            if (s[i] == '1') {
                while (s[i] == '1' && i < len) cnt1++, i++;
                c1++;
                // i -- ;
            }
            else {
                while (s[i] == '0' && i < len) cnt0++, i++;
                c0++;
                // i --;
            }
            // i--;
        }
        // cout << "*** ";
        // cout << cnt0 << ' ' << cnt1 << endl;
        // cout << cnt1 * a + b + cnt0 * a + c0 * b << endl;
        // cout << "(*" << c0 <<  ' ' << c1 << endl;
        cout << a * len + b*(min(c0, c1) + 1) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}
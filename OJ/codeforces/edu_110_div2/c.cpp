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

const int N = 2e5 + 10;
char s[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while (t --) {
        cin >> s + 1;
        int l = 1;
        ll res = 0;
        int j1 = 0, j0 = 0, o1 = 0, o0 = 0;
        for (int i = 1; s[i]; i++) {
            if (s[i] == '0')
                if (i & 1) j0 ++;
                else o0 ++;
            if (s[i] == '1')
                if (i & 1) j1++;
                else o1 ++;

            while (j0 && j1 || j0 && o0 || j1 && o1 || o0 && o1) {
                if (s[l] == '1') {
                    if (l & 1) j1 --;
                    else o1 --;
                }
                else if (s[l] == '0') {
                    if (l & 1) j0 --;
                    else o0--;
                }
                l++;
            }
            res += i - l + 1;
        }
        cout << res << endl;
    }
    return 0;
}
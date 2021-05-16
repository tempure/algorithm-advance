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


//it's very brutal :(

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s; cin >> s;
    int ans = 0;

    for (int i = 0; i <= 9999; i++) {
        vector<bool> flag(10);
        int x = i;
        for (int j = 0; j < 4; j++) {
            flag[x % 10] = true;
            x /= 10;
        }

        bool flag2 = true;
        for (int j = 0; j < 10; j++) {
            if (s[j] == 'o' && !flag[j]) flag2 = false;
            if (s[j] == 'x' && flag[j]) flag2 = false;
        }
        ans += flag2;
    }

    cout << ans << endl;

    return 0;
}

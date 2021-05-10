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

const int N = 1010;
char str[N * N];
ll ans = 0;

bool check(char str[]) {
    // cout << strlen(str) << endl;
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < len / 2; i ++, j --) {
        if (str[i] != str[j]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << check("9009") << endl;
    cout << check("11111") << endl;
    cout << check("12321") << endl;
    cout << check("213124") << endl;
    cout << "*****************" << endl;

    ll res = 0;
    for (int i = 999; i >= 100; i --)
        for (int j = 999; j >= 100; j--) {
            res = i * j;
            if (check(itoa(res, str, 10))) {
                // cout << str << endl;
                ans = max(ans, res);
            }
        }
    cout << ans << endl;

    return 0;
}
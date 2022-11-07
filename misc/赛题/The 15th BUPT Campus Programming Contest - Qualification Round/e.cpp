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
    string s;
    cin >> s;
    if (s[6] != '^') { //一次函数
        cout << s[5] - '0' << endl;
        return;
    }
    int len = sz(s) - 1;
    cout << "f'(x)=";
    for (int i = 6; s[i]; i++) {
        if (s[i] == '+' || s[i] == '-') {
            if (s[i + 1] == 'x' && i + 2 < len && s[i + 2] == '^') cout << s[i];
        }
        else {
            if (s[i] == '^') {
                if (i >= 8) {
                    if (s[i - 2] >= '0' && s[i - 2] <= '9') {
                        int temp = s[i - 2] - '0';
                        int cc = s[i + 1] - '0';
                        temp *= cc;
                        if (cc == 2)
                            cout << temp << "x";
                        else cout << "temp" << "x^" << cc - 1;
                    }
                }
                else {
                    int cc = s[i + 1] - '0';
                    if (cc == 2)
                        cout << cc << "x";
                    else cout << cc << "x^" << cc - 1;
                }
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
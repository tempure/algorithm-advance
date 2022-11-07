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

int main() {
    ios::sync_with_stdio(false);

    int K;
    string S;
    cin >> K >> S;
    S += '.';
    reverse(S.begin(), S.end());
    vector<int> dp(1 << K, 0);

    auto update = [&](int x) -> void {
        if (x >= 1 << (K - 1)) {
            dp[x] = 1 + (S[x] == '?');
            return;
        }

        if (S[x] == '1')
            dp[x] = dp[2 * x];
        else if (S[x] == '0')
            dp[x] = dp[2 * x + 1];
        else
            dp[x] = dp[2 * x] + dp[2 * x + 1];
    };

    auto propagate_up = [&](int x) -> void {
        while (x > 0) {
            update(x);
            x /= 2;
        }
    };

    for (int x = (1 << K) - 1; x > 0; x--)
        update(x);

    int Q;
    cin >> Q;

    for (int q = 0; q < Q; q++) {
        int p;
        char ch;
        cin >> p >> ch;
        p = (1 << K) - p;
        S[p] = ch;
        propagate_up(p);
        cout << dp[1] << '\n';
    }
}
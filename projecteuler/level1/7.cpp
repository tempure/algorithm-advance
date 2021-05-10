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

bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i <= n / i; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int cnt = 0;

    for (ll i = 2; i; i++) {
        if (is_prime(i)) cnt ++;
        if (cnt == 10001) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}

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

const int N = 4e6 + 10;
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    f[1] = 1, f[2] = 2;
    for (int i = 3; i <= N; i++) f[i] = f[i - 1] + f[i - 2];

    for (int i = 1; i <= 10; i++) cout << f[i] << ' ';
    cout << endl;

    for (int i = 1; i <= N; i++)
        if (f[i] > 4e6) {
            cout << "**** " << i << endl;
            break;
        }
    cout << f[32] << endl;
    cout << f[33] << endl;

    ll res = 0;
    for (int i = 1; i <= 32; i++) {
        if (f[i] & 1) continue;
        res += f[i];
    }
    cout << res << endl;

    return 0;
}
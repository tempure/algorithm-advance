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

int count(int x) {
    int cnt = 0;
    for (int i = 1; i <= x / i; i++)
        if (x % i == 0) {
            cnt ++;
            if (i != x / i) cnt++;
        }
    return cnt + 1; //算上自身
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 1; i; i++) {
        if (count(i * (i + 1) / 2) > 500) {
            cout << i * (i + 1) / 2 << endl;
            break;
        }
    }

    return 0;
}
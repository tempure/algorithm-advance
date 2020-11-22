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
//snippet-head


//exgcd模板

// long long

ll exgcd(ll a, ll b, ll &x, ll & y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

//int

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

//void 版本
void exgcd(ll a, ll b, ll &x, ll & y) {
    if (!b)
        x = 1, y = 0;
    else {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}
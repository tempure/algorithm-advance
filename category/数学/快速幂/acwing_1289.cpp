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
const ll mod = 200907;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

//先证明如果一个等比数列的前三项都是整数，那么整个数列都是整数
//前三项abc，假设a,b，c都是整数
//如果a不能整除b，那么第三项c就是(b^2)/a 不是整数，矛盾


int qmi(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = (ll)res * a % mod;
        a = (ll)a  * a % mod;
        k >>= 1;
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n --) {
        int a, b, c, k;
        scanf("%d%d%d%d", &a, &b, &c, &k);
        if (a + c == 2 * b) printf("%lld\n", (a + (ll)(k - 1) * (b - a)) % mod);
        else printf("%lld\n", ((ll)a * qmi(b / a , k - 1)) % mod);
    }
    return 0;
}
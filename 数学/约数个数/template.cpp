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


//倍数法求正约数集合模板

const int N = 10000;

vi factor[N];
int n;

void calc(int n) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n / i; j++)
            factor[i * j].push_back(i);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < factor[i].size(); j++)
            printf("%d ", factor[i][j]);
        puts("");
    }
}

int main() {
    scanf("%d", &n);
    calc(n);

    return 0;
}
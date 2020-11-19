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

//分解质因数模板

const int N = 100010; // 数组开sqrt(N) 的数量级即可 看循环的次数
int p[N], c[N]; //p存储质因子 c存储幂次

int n, m;
//复杂度 O(sqrt(n))
void divide(int n) {
    m = 0;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            p[++m] = i; c[m] = 0;
            while (n % i == 0) n /= i, c[m]++;
        }
    }

    if (n > 1) p[++m] = n, c[m] = 1;

    for (int i = 1; i <= m; i++)
        cout << p[i] << ' ' << c[i] << endl;
    cout << endl;
}

int main() {
    int x;
    cin >> n;
    while (n --) {
        cin >> x;
        divide(x);
    }

    return 0;
}
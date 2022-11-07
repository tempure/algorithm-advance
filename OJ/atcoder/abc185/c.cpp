#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define endl '\n'
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

const int N = 5010;
int primes[N], cnt;
int sum[N];
bool st[N];
int p;

//求组合数 C(l-1,11) 不取模
//直接套板子即可

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}
int get(int n) { //求出n!中包含的p的个数
    int res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}
ll qmi(int a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res *= a;
        b >>= 1;
        a = a * a;
    }
    return res;
}
//高精度乘法
vector<int> mul(vector<int> &a, int b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i++) {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        c.push_back(t % 10);
        t /= 10;
    }
    return c;
}

void solve() {
    int a, b;
    cin >> a;
    a -= 1;
    b = 11;
    get_primes(a);  //求出1 ~ a 中所有质数
    for (int i = 0; i < cnt; i++) {
        p = primes[i];
        sum[i] = get(a) - get(b) - get(a - b); //p的次数,0就相当于不减
    }
    vector<int> res;  //高精度乘法
    res.push_back(1);
    for (int i = 0; i < cnt; i++)
        res = mul(res, qmi(primes[i], sum[i]));
    //输出答案
    for (int i = res.size() - 1 ; i >= 0; i--) cout << res[i];
    cout << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
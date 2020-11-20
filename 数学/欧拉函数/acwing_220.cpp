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

//gcd(a,b) == p, 那么gcd(a/p, b/p) == 1，枚举n内所有素数
//而求1~n中有序互质对x，y的个数，可以令y >= x, 当y = x时，有且只有y = x = 1互质，
//当y > x时，确定y以后符合条件的个数x就是phiy
// 所以有序互质对的个数为（1 ~ n/p）的欧拉函数之和乘2减1（要求的是有序互质对，乘2以后减去（1， 1）多算的一次）
// 那么就只需要先筛出欧拉函数再求个前缀和就可以了

//注意:这里的数对的概念就是坐标(x,y) 是有顺序之分的

const int N = 1e7 + 10;

int n;
int primes[N], cnt;
int phi[N]; //欧拉函数
bool v[N];
ll s[N];  //欧拉函数值的前缀和


void get_euler(int n) { //线性筛求欧拉函数
    memset(v, 0, sizeof v);
    cnt = 0;

    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!v[i]) {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            int t = primes[j] * i;
            v[t] = 1;
            if (i % primes[j] == 0) {
                phi[t] = phi[i] * primes[j];
                break;
            }
            phi[t] = phi[i] * (primes[j] - 1);
        }
    }

    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + phi[i];
}

int main() {
    cin >> n;
    get_euler(n);
    ll res = 0;

    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        res += s[n / p] * 2 - 1;
    }

    cout << res << endl;

    return 0;
}
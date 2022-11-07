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


//线性筛一次 然后v数组记录是不是素数，如果v[i]是false 说明i是素数
//从3开始遍历到n如果 i, x- i 都是素数那么直接输出 然后break即可找到

const int N = 1000010;
bool v[N];
int primes[N];
int cnt; //记录素数的个数

void prime(int n) {
    memset(v, 0, sizeof v);
    for (int i = 2; i <= n; i++) {
        if (!v[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    prime(N);
    int x;
    while (cin >> x , x) {
        bool flag = false;
        for (int i = 3; i < x; i++)
            if (!v[i] && !v[x - i]) {
                flag = true;
                cout << x << " = " << i << " + " << x - i << endl;
                break; //因为只输出最小和最大的组合 所以要一定break
            }
        if (flag == false)  puts("Goldbach's conjecture is wrong.");
    }
    return 0;
}
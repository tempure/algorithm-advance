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


//题意:给出N个数 求出对于每个数 有多少个其他的数(不包括自己) 是自己的约数
//直接打表 处理1e6范围内的所有数
//对于每个数把这个数出现的次数累加到它的倍数的次数上去 也就是求出1~N中有多少个数有约数(1,2.....N)
//由阶乘分解那题可知复杂度O(N * logN) N是枚举每个数

const int N = 1000010;
int n;
int a[N], cnt[N], s[N]; // cnt保存每个数出现的次数  s保存约数的总个数

int main() {

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        cnt[a[i]] ++;
    }

    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j += i)  //枚举i的所有倍数
            s[j] += cnt[i];

    for (int i = 0; i < n; i++) printf("%d\n",  s[a[i]] - 1); //减去自己本身

    return 0;
}
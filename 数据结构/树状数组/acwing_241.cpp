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

//依次枚举每个点为最低点或者最高点
//从然后划分为左边和右边 计算左边有多少个y比当前点的y高或者低  左右乘起来就是当前集合的总数、
//求出所有点代表的集合 然后求和即可
//在这个过程中 扫描到一个y比当前y大的点 那么当前y增加1 还需要统计区间和2个功能就可以用树状数组实现了

const int N = 200010;

int n;
int a[N];
int tr[N]; //树状数组
int gr[N], lo[N]; //每个位置前面的位置 有多少位置的高度比当前位置的高度高 / 低

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) { //单点增加 修改全部父结点
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

/*
从左向右依次遍历每个数a[i]，使用树状数组统计在i位置之前所有比a[i]大的数的个数、以及比a[i]小的数的个数。
统计完成后，将a[i]加入到树状数组。

从右向左依次遍历每个数a[i]，使用树状数组统计在i位置之后所有比a[i]大的数的个数、以及比a[i]小的数的个数。
从右往左时由于已经处理过i位置前面的比i位置的高度大的和小的数量，直接用左边的位置的乘上右边即可，


这个理解还是有点难度的，要把位置i看成横坐标的话，那么高度就得看成纵坐标，从左往右扫的时候只会求出这个点左边比自己小的和大的
第二次从右往左扫之前要先清空树状数组，然后重新扫 不然会重复 但是左边的结果已经存在了gr和lo数组中
*/

int main() {

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++) {
        int y = a[i]; //当前点的高度
        gr[i] = sum(n) - sum(y);
        lo[i] = sum(y - 1);
        add(y, 1);
    }
    //清空 然后倒着扫一次
    memset(tr, 0, sizeof tr);

    ll res1 = 0, res2 = 0; //v以及^
    for (int i = n; i; i--) {
        int y = a[i];
        res1 += gr[i] * 1ll * (sum(n) - sum(y));
        res2 += lo[i] * 1ll * (sum(y - 1));
        add(y, 1);
    }

    printf("%lld %lld\n", res1, res2);

    return 0;
}
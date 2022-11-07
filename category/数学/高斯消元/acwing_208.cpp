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

/*
开关问题：用x1,x2...xn表示n个开关有没有按，1代表按0代表不按
方案数取决于最后的自由变量个数假设k个自由变量，n是行数/列数
那么2^k就是答案
*/

const int N = 30;
int n; int a[N][N];

int gauss() {
    int r, c;
    for (r = 1, c = 1; c <= n; c++) {
        //找主元
        int t = r;
        for (int i = r + 1; i <= n; i++)
            if (a[i][c])
                t = i;
        if (!a[t][c]) continue; //没有主元
        //将主元所在行交换到最上方
        for (int i = c; i <= n + 1; i++) swap(a[t][i], a[r][i]);
        //消掉
        for (int i = r + 1; i <= n; i++) //将1下边的全部消成0
            if (a[i][c])
                for (int j = c; j <= n + 1; j++)
                    a[i][j] ^= a[r][j];   //  下边如果是0 那异或1还是0  如果是1  那和1异或之后就是0了
        r++;
    }

    int res = 1;
    if (r < n + 1) {
        for (int i = r; i <= n; i++) {
            if (a[i][n + 1]) return -1;
            res *= 2;
        }
    }
    return res;
}

int main() {
    int t;  scanf("%d", &t);
    while (t--) {
        memset(a, 0, sizeof a); //每次清空a
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i][n + 1]); //最终的状态
        for (int i = 1; i <= n; i++) {
            int t; scanf("%d", &t);
            a[i][n + 1] ^= t; //方程组最后边一列是状态有没有发生变化，而不关心最终的结果是什么
            a[i][i] = 1; //开关按一次自己改变自己的状态
        }

        int x, y;
        //对第y个方程的第x个系数会产生影响
        //每一行方程的所有系数就是所有会对这个开关产生影响的开关
        while (scanf("%d%d", &x, &y), x || y) a[y][x] = 1;
        int t = gauss();
        if (t == -1) puts("Oh,it's impossible~!!");
        else printf("%lld\n", t);
    }

    return 0;
}
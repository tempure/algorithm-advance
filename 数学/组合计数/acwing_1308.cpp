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

const int N = 150; //高精度计算的位数

int k, x;
int f[1000][100][N];

int qmi(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>=  1;
    }
    return res;
}

//第一次add调用之后 c数组里面，也就是传进来的f[][]的第三维已经存着逆序的结果，
//所以之后的相加都是顺理成章逆序存储结果
void add(int c[], int a[], int b[]) {
    for (int i = 0, t  = 0 ; i < N; i++) {
        t += a[i] + b[i];
        c[i] = t % 10;
        t /= 10;
    }
}

int main() {
    scanf("%d%d", &k, &x);

    int n = qmi(x % 1000, x, 1000); //注意开始计算的时候取模

    //C(n - 1, k - 1)组合数就是结果
    //C(1000, 100) 不会超时 直接用最简单的递推即可
    //递推法 杨辉三角 复杂度O(n * m)
    //由于最后的结果不是组合数取模  显然要用高精度


    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i && j < k; j++) //到k - 1
            if (!j) f[i][j][0] = 1;
            else add(f[i][j], f[i - 1][j], f[i - 1][j - 1]); //f[i][j] = f[i - 1][j] + f[i - 1][j - 1]

    int *g = f[n - 1][k - 1];
    int i = N - 1;
    while (!g[i]) i --; //找到最高位不是0的位置 逆序输出 高精度的结果是逆序存储的

    while (i >=  0) printf("%d", g[i--]);

    return 0;
}
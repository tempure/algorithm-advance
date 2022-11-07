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


//Fn = [f[n], f[n + 1], s[n], p[n]]
//T[n] = 1*f[1] + 2 * f[2] + 3 * f[3]....
//p[n] = n * s[n] - T[n] = p[n - 1] + s[n - 1]
//p[n + 1] - p[n] = s[n]
//s[n] = f[1] + f[2] + .... + f[n]
//递推F[n] 和 F[n + 1]的关系即可

//Fn = [f[n], f[n + 1], s[n], p[n]] * [0, 1, 0, 0]
//                                    [1, 1, 1, 0]
//                                    [0, 0, 1, 1]
//                                    [0, 0, 0, 1]

//F[1] = [1, 1, 1, 0]
//最后的T[n] = n * s[n] - p[n]

//需要实现1 * 4的矩阵和4 * 4的矩阵相乘 但是可以把1行的矩阵看成4行，剩余的三行都是0的矩阵

const int N = 4;
int n, m;

void mul(int c[][N], int a[][N], int b[][N]) { //c = a * b //二维相乘
    int temp[N][N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                temp[i][j] = (temp[i][j] + (ll)a[i][k] * b[k][j]) % m;
    memcpy(c, temp, sizeof temp);
}

int main() {
    cin >> n >> m;
    int f1[N][N] = {1, 1, 1, 0}; //直接把f1(F) 也初始化为4 * 4矩阵 就可以少些一个矩阵相乘的函数
    int a[N][N] = {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 1}
    };

    int k = n - 1; //递推n - 1次
    while (k) {
        if (k & 1) mul(f1, f1, a);
        mul(a, a, a);
        k >>= 1;
    }
    cout << (((ll)n * f1[0][2] - f1[0][3]) % m + m) % m << endl;
    return 0;
}
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
// const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
// ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
// ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head


const int N = 25;
int n, m, mod;
char str[N];
int ne[N]; //kmp
// a[i][j] 表示长度相邻的两个串，后缀和不吉利的串的前缀匹配长度从i变成j的方案数
//这个方案数是定值 可以预处理出来  也就是递推矩阵的元素
int a[N][N];

void mul(int c[][N], int a[][N], int b[][N]) { //c = a * b //二维相乘
    int temp[N][N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                temp[i][j] = (temp[i][j] + (ll)a[i][k] * b[k][j]) % mod;//此处可选取模 % m;
    memcpy(c, temp, sizeof temp);
}

ll qmi(int k) {
    int f0[N][N] = {1}; //就只有一种方案 就是0位的答案
    //f[i][j] 表示当前已经有i位答案，且当前答案的后缀和不吉利的串匹配的前缀长度为j

    while (k) {
        if (k & 1) mul(f0, f0, a);
        mul(a, a, a);
        k >>= 1;
    }

    ll res = 0;
    for (int i = 0; i < m; i++) res = ((res + f0[0][i]) % mod + mod) % mod;

    return res;
}

int main() {
    cin >> n >> m >> mod;
    cin >> str + 1;

    //kmp 预处理next数组
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && str[j + 1] != str[i]) j = ne[j];
        if (str[j + 1] == str[i]) j++;
        ne[i] = j;
    }

    //初始化a[][]
    for (int j = 0; j < m;  j++)
        for (int c = '0'; c <= '9'; c++) {
            int k = j;
            while (k && str[k + 1] != c) k = ne[k];
            if (str[k + 1] == c) k++;
            if (k < m) a[j][k] ++; //长度j可以转移到长度k
        }

    //F[n] = F[0] * A ^ n
    cout << qmi(n) << endl;


    return 0;
}
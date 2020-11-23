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

//矩阵乘法模板

const int N = 3;

void mul(int c[], int a[], int b[][N]) { //c = a  * b 一维乘二维
    int temp[N] = {0};
    for (int i = 0; i < N; i++) //列
        for (int j = 0; j < N; j++) //行
            temp[i] = (temp[i] + (ll)a[j] * b[j][i]); //这里可选是否取模
    memcpy(c, temp, sizeof temp); //这里要写temp  因为传进来的c只是一个指针
}

//对于一行的矩阵*二维的矩阵
//可以将一行的矩阵初始化为二维的，除了第一行其余 行为0即可
void mul(int c[][N], int a[][N], int b[][N]) { //c = a * b //二维相乘
    int temp[N][N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                temp[i][j] = (temp[i][j] + (ll)a[i][k] * b[k][j]);//此处可选取模 % m;
    memcpy(c, temp, sizeof temp);
}
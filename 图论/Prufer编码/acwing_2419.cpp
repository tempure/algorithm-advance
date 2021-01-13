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
//head

/*
O(n) 做法 prufer序列
一个无向树的prufer编码只有n-2位，默认最大的编号的点不会出现
每删掉一个点就会记录一位，最后剩下2个点没删，所以一共有n-2位
*/

const int N = 100010;

int n, m;
int f[N], d[N], p[N];

void tree2prufer() {
    for (int i = 1; i < n; i++) {
        scanf("%d", &f[i]);
        d[f[i]] ++; //此时的d[]是每个点的出度
    }

    for (int i = 0, j = 1; i < n - 2; j++) {
        while (d[j]) j++;
        p[i ++] = f[j];
        while (i < n - 2 && --d[p[i - 1]] == 0 && p[i - 1] < j)
            p[i++] = f[p[i - 1]]; //p[]记录 prufer序列
    }

    for (int i = 0; i < n - 2; i++) printf("%d ", p[i]);
}

void prufer2tree() {
    for (int i = 1; i <= n - 2; i++) {
        scanf("%d", &p[i]);
        d[p[i]]++; //此时的d记录每个节点的子节点的个数
    }
    p[n - 1] = n;

    for (int i = 1, j = 1; i < n; i++, j++) {
        while (d[j]) j ++;
        f[j] = p[i]; //第一个子节点个数为0的点j
        while (i < n - 1 && --d[p[i]] == 0 && p[i] < j)
            f[p[i]] = p[i + 1], i ++; //p[]是prufer序列
    }

    for (int i = 1; i <= n - 1; i++) printf("%d ", f[i]);
}

int main() {
    scanf("%d%d", &n, &m);
    if (m == 1) tree2prufer();
    else prufer2tree();

    return 0;
}
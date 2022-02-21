#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
// head

//这个题到底啥意思。。。
//样例改为如下：（？）
/*
10
2 8 2 8 8 8 2 8 8 2
*/

//upd:https://www.bilibili.com/video/BV1gR4y1j76r
//这题是最上面k个必须数字是k才会消失

const int N = 201000;
int n, p[N], s[N];
int main() {
    scanf("%d", &n);
    int t = 0;
    rep(i, 0, n) {
        int x;
        scanf("%d", &x);
        p[++t] = x;
        if (t == 1 || p[t] != p[t - 1]) s[t] = 1; else s[t] = s[t - 1] + 1;
        if (s[t] == x) t -= x;
        printf("%d\n", t);
    }
}
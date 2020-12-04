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

//f[a][b]为状态 a表示一个石子独立成堆的数量
// b表示大于一个石子的堆数+这些石子的总数 - 1
//b中不包含单个成堆的石子

const int N = 55, M = 50050;
int f[N][M];

int dp(int a, int b) {
    int &v = f[a][b];
    if (v != -1)  return v;
    if (!a) return v = b % 2; //所有堆都大于一个石子 判断奇偶性即可

    if (b == 1) return dp(a + 1, 0); //此时b只有一个独立石子 那就直接归到a中

    if (a && !dp(a - 1, b)) return v = 1;  //a中取一个
    if (b && !dp(a, b - 1)) return v = 1; //b中取一个 或者合并b中2个 能到这一个if说明b中至少2个石子
    if (a >= 2 && !dp(a - 2, b + (b ? 3 : 2))) return v = 1; //合并a中的2个
    if (a && b && !dp(a - 1, b + 1)) return v = 1; //合并a中的一个和b中的一个

    return v = 0;
}

int main() {
    memset(f, -1, sizeof f);

    int T;
    scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        int a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            if (x == 1) a ++;
            else b += b ? x + 1 : x;
        }
        if (dp(a, b)) puts("YES");
        else puts("NO");
    }
}

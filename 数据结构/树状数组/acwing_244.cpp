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

//从后往前扫 i位置的排名就是剩下的牛里面a[i] + 1 剩下是指前面没扫的包括当前位置的牛
//本质问题就是从剩余的数中找出第k小的数 以及删除某一个数的操作
//用数组的下标表示高度 所有元素置为1表示还没被删，从后往前扫
//对于每个a[i]也就是第k高 当tr[j]的某个前缀等于a[i]的时候，也就是 这时候的下标j就是答案

//平衡树可以解决但是太难写 这里用树状数组解决

const int N = 100010;
int n; int a[N];
int ans[N];
int tr[N];

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) scanf("%d", &a[i]); //这里第一个0不读入默认0

    for (int i = 1; i <= n; i++) add(i, 1); //初始化树状数组

    for (int i = n; i; i--) {
        int k = a[i] + 1;

        //二分
        int l = 1, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (sum(mid) >= k) r = mid;
            else l = mid + 1;
        }
        ans[i] = r;
        add(r, -1);
    }

    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);

    return 0;
}
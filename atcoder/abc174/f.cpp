#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define endl '\n'
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

//莫队板子

const int N = 5e5 + 10, M = N, S = 1000010;
int n, m, len;
int w[N],  ans[M];
struct Query {
    int id, l, r;
} q[M];
int cnt[S]; //哈希数组 每个数出现的次数
int get(int x) {
    return x / len;
}
bool cmp(const Query& a, const Query& b) {
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}
void add(int x, int &res) {
    if (!cnt[x]) res ++;
    cnt[x] ++;
}
void del(int x, int &res) {
    cnt[x] --;
    if (!cnt[x]) res --;
}
int main() {
    scanf("%d", &n);
    scanf("%d", &m);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    len = sqrt((double) n * n / m);
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    sort(q, q + m, cmp);
    //j是左边界指针 i是右边界指针 w[]下标都是从1开始
    //初始i=0,j=1是为了正确计算[1,1]的结果
    for (int k = 0, i = 0, j = 1, res = 0; k < m; k ++) {
        int id = q[k].id, l = q[k].l, r = q[k].r;
        while (i < r) add(w[++i], res);
        while (i > r) del(w[i--], res);
        while (j < l) del(w[j++], res);
        while (j > l) add(w[--j], res);
        ans[id] = res;
    }
    for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
    return 0;
}
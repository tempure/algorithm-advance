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

//区间修改 区间求和 m次查询
//在差分数组上要求远数组的和 需要求2层前缀和 差分数组用树状数组存
//由于是在线询问 每次区间求和都要2层 平方复杂度 超时

//技巧：所有要求的数补齐成一个方阵，然后维护2个前缀和即可
//(b1 + b2 + ...+bx)*(x + 1) - (b1 - 2 * b2 - 3 * b3 - .... x * bx)
//维护bi的前缀和和i*bi的前缀和 并行操作


const int N = 100010;
int n, m;
int a[N];
ll tr1[N]; //bi
ll tr2[N]; //i * bi前缀和

int lowbit(int x) {
    return x & -x;
}

void add(ll tr[], int x, ll c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

ll sum(ll tr[], int x) {
    ll res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

ll prefix_sum(int x) {
    return sum(tr1, x) * (x + 1) - sum(tr2, x);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        int b = a[i] - a[i - 1];
        add(tr1, i, b);
        add(tr2, i, 1ll * b * i);
    }

    while (m --) {
        char op[2];
        int l, r, d;
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'Q') {
            printf("%lld\n", prefix_sum(r) - prefix_sum(l - 1));
        }
        else {
            scanf("%d", &d);
            add(tr1, l, d), add(tr2, l, l * d);
            add(tr1, r + 1, -d), add(tr2, r + 1, (r + 1) * -d);
        }
    }
    return 0;
}

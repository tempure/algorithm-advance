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
带修莫队：在朴素莫队的基础上加一个时间戳
块外区间排序的原则不变，块内排序的最后一个关键字是时间戳
在横坐标区间上，右指针来回扫，在纵坐标时间戳上，tt指针也是来回扫
每一个时间戳对应的状态，也就是二维状态坐标系中的一行，就是进行了一次修改操作的状态
用巧妙的swap()操作可以进行修改以及撤销操作的交替进行,也就是删除和添加元素
分块区间长度计算可得为cbrt(n*t)+1,加1是为了防止整取为0，t是修改操作的总次数
*/

const int N = 10010, S = 1000010;

int n, m, mq, mc, len; //mq是询问计数器 mc是修改计数器
int w[N], cnt[S], ans[N];

struct Query {
    int id, l, r, t; //t是时间戳
} q[N];

struct Modify {
    int p, c;
} c[N];

int get(int x) {
    return x / len;
}

bool cmp(const Query& a, const Query& b) {
    int al = get(a.l), ar = get(a.r);
    int bl = get(b.l), br = get(b.r);
    if (al != bl) return al < bl; //不同块 左端点升序
    if (ar != br) return ar < br; //块内先按照右端点升序
    return a.t < b.t; //先按区间端点排序 端点相同 按照修改时间戳排序
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
    scanf("%d%d", &n, &m); //m个询问
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 0; i < m; i++) {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        if (*op == 'Q') mq++, q[mq] = {mq, a, b, mc};
        else c[++mc] = {a, b};
    }

    len = cbrt((double)n * mc) + 1; //+1防止开方取整后为0
    sort(q + 1, q + mq + 1, cmp);

    for (int i = 0, j = 1, tt = 0, k = 1, res = 0; k <= mq; k++) {
        int id = q[k].id, l = q[k].l, r = q[k].r, tm = q[k].t;
        while (i < r) add(w[++i], res);
        while (i > r) del(w[i--], res);
        while (j < l) del(w[j++], res);
        while (j > l) add(w[--j], res);

        //处理时间戳
        while (tt < tm) { //当前tt指针所在的时间戳落后于要处理的询问的区间
            tt ++;
            if (c[tt].p >= j && c[tt].p <= i) {
                del(w[c[tt].p], res);
                add(c[tt].c, res);
            }
            swap(w[c[tt].p], c[tt].c); //交换来更新修改记录
        }
        while (tt > tm) { //当前tt指针所在的时间戳先于要处理的询问的区间
            if (c[tt].p >= j && c[tt].p <= i) {
                del(w[c[tt].p], res);
                add(c[tt].c, res);
            }
            swap(w[c[tt].p], c[tt].c); //倒序撤销修改记录
            tt--; //注意要先撤销再修改时间戳
        }
        ans[id] = res;
    }

    for (int i = 1; i <= mq; i++) printf("%d\n", ans[i]);

    return 0;
}
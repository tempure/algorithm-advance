/*给定一个长度为n的序列a1,a2,…,an以及一个整数k。m次询问区间[l,r]求出共有多少个数对(i,j)满足l<=i<j<=r且ai^aj的结果在二进制下恰好有k个1
此题的数对(x,y)和(y,x)视为相同的数对 不需要重复计算
配对：x^y中二进制位为1的个数为k，则视为x与y配对
f[]表示从w[1]~w[i]中和w[i+1]配对的元素个数
g[]表示从当前二次离线计算的前驱[1,i]中能和x配对的元素个数 二次离线计算前驱是递增的
二次离线莫队:主要是前缀和的思想，对于每一个位置pos，给出一个询问区间[l,r]
计算出[l,pos-1]中和pos位置的元素配对的元素个数，设为s[pos],然后求s[]的前缀和即可
莫队要用上一个算出的询问区间答案来更新下一个询问区间
根据f[]和g[]的定义，在莫队更新区间的过程中:
1.如果右指针移动，前驱[1,L]和右指针更新的区间的配对数量无法容易求出来更新答案
2.如果左指针移动，前驱[1,R]和左指针更新的区间的配对数量无法容易求出来更新答案
那么就把这些不容易更新的区间以及与之匹配的前驱保存起来，之后再离线计算一次即可。复杂度O(N*sqrt(N))*/
typedef long long ll;
const int N = 100010;
int n, m, k, len;
int w[N];
ll ans[N]; //数对平方级别会爆掉int
int f[N]; //f[i]表示从w[1]~w[i]中和w[i+1]配对的元素个数
int g[N]; //g[x]表示从当前二次离线计算的前驱[1,i]中能和x配对的元素个数 二次离线计算前驱是递增的
struct Query {
    int id, l, r;
    ll res; //res是没有二次离线之前保存的临时结果 也就是只计算了SR或者SL的部分的答案
} q[N];
struct Range { //二次离线需要处理的和前缀配对的小区间
    int id, l, r, t; //t是加还是减的标记
};
vector<Range> range[N]; //range[i]就是需要和前驱[1,i]进行配对计算的所有小区间
inline int get_count(int x) { //返回一个数的二进制中1的位数
    int res = 0;
    while (x) res += x & 1, x >>= 1;
    return res;
}
inline int get(int x) {
    return x / len;
}
bool cmp(const Query &a, const Query &b) {
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    vector<int> nums; //预处理所有二进制中1的位数为k的数
    for (int i = 0; i < 1 << 14; i++)
        if (get_count(i) == k)
            nums.push_back(i);
    for (int i = 1; i <= n; i++) {
        for (auto y : nums) ++ g[w[i] ^ y];
        f[i] = g[w[i + 1]]; //f[i] = g[w[i+1]] 计算出f[]数组
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    len = sqrt(n);
    sort(q, q + m, cmp);
    //第一次离线莫队
    for (int i = 0, L = 1, R = 0; i < m; i++) {
        int l = q[i].l, r = q[i].r;
        if (R < r) range[L - 1].push_back({i, R + 1, r, -1});
        while (R < r) q[i].res += f[R ++ ];
        if (R > r) range[L - 1].push_back({i, r + 1, R, 1});
        while (R > r) q[i].res -= f[ -- R];
        if (L < l) range[R].push_back({i, L, l - 1, -1});
        while (L < l) q[i].res += f[L - 1] + !k, L ++ ;
        if (L > l) range[R].push_back({i, l, L - 1, 1});
        while (L > l) q[i].res -= f[L - 2] + !k, L -- ;
    }
    //第二次离线莫队O(N)
    memset(g, 0, sizeof g);
    for (int i = 1; i <= n; i++) { //i是当前计算的前驱的指针
        for (auto y : nums) ++g[w[i] ^ y];
        for (auto &rg : range[i]) { //一次性计算一个前驱所有需要处理的区间
            int id = rg.id, l = rg.l, r = rg.r, t = rg.t;
            for (int x = l; x <= r; x++)
                q[id].res += g[w[x]] * t; //g[w[x]]就是当前的前驱[1,i]中和w[x]配对的元素数量
        }
    }
    //求前缀和
    for (int i = 1; i < m; i++) q[i].res += q[i - 1].res;
    for (int i = 0; i < m; i++) ans[q[i].id] = q[i].res;
    for (int i = 0; i < m; i++) printf("%lld\n", ans[i]);
    return 0;
}
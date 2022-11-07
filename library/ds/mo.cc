/*SDOI2009《HH的项链》：给定一个序列，长度N，M个区间询问，求该区间内不同元素的个数
1<=N<=50000,1<=M<=2e5,1<=L<=R<=N
不同块的询问按照左端点升序，块内按照右端点升序,处理完一个块内所有询问的区间，才会处理下一个块。分块区间长度的计算：假设块长为a，序列长为n，注意a是int类型
左指针移动数量级m * a, m是询问数量,右指针移动数量级n * n / a 让左右指针移动的次数尽量相等 解出a = sqrt(n*n/m)
对于左端点在同一个块内的询问，这些询问的右端点是升序的，所以每次处理一个块的时候，右指针扫描是递增的，也就是O(N)复杂度。但是下一个块的时候右指针有可能需要扫回去到左边,一共有大约sqrt(N)个块，所以复杂度就是O(N*sqrt(N))*/
const int N = 50010, M = 200010, S = 1000010;
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
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    scanf("%d", &m);
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
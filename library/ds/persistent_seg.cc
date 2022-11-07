/*
例题：区间第k小 O((N+M)logN)M次询问
给定长度为N的整数序列A，下标为 1∼N。
现在要执行M次操作，其中第i次操作为给出三个整数li,ri,ki，求A[li],A[li+1],…,A[ri](即A的下标区间[li,ri])中第ki小的数是多少。
*/
#define all(x) (x).begin(), (x).end()
const int N = 100010;
int n, m;
int a[N];
vector<int> nums;
struct Node {
    int l, r; //左子节点 右子节点 不是区间
    int cnt; //有多少个点落在 离散化之后的下标范围内
} tr[N * 4 + N * 17]; //额外多N* logN空间 没有修改 只有询问
int root[N]; //每个版本的根节点
int idx;
int find(int x) {
    return lower_bound(all(nums), x) - nums.begin();
}
int build(int l, int r) {
    int p = ++idx;
    if (l == r) return p;
    int mid = l + r >> 1;
    tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
    return p;
}
//上一个版本的root 数组的左边界下标 右边界下标 a[i]离散化之后的下标值
int insert(int p, int l, int r, int x) {
    int q = ++idx;
    tr[q] = tr[p]; //复制
    if (l == r) {
        tr[q].cnt ++;
        return q;
    }
    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = insert(tr[p].l, l, mid, x);
    else tr[q].r = insert(tr[p].r, mid + 1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
    return q;
}
//后边的版本 前面的版本 左右查询区间 第k大
int query(int q, int p, int l, int r, int k) {
    if (l == r) return r;
    int cnt  = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
    int mid = l + r >> 1;
    if (k <= cnt) return query(tr[q].l, tr[p].l, l, mid, k);
    else return query(tr[q].r, tr[p].r, mid + 1, r, k - cnt);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        nums.push_back(a[i]);
    }
    sort(all(nums));
    nums.erase(unique(all(nums)), nums.end()); //离散化
    root[0] = build(0, nums.size() - 1);
    for (int i = 1; i <= n; i++) root[i] = insert(root[i - 1], 0, nums.size() - 1, find(a[i]));
    while (m --) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", nums[query(root[r], root[l - 1], 0, nums.size() - 1, k)]);
    }
    return 0;
}
/*各操作复杂度：插入一个数O(logN),求堆顶O(1),删除堆顶O(logN),合并2棵左偏树O(logN)
模板题：维护一个小根堆的集合，初始时集合是空
该集合需要支持如下四种操作：
1 a，在集合中插入一个新堆，堆中只包含一个数 a。
2 x y，将第 x 个插入的数和第 y 个插入的数所在的小根堆合并。数据保证两个数均未被删除。若两数已在同一堆中，则忽略此操作。
3 x，输出第 x 个插入的数所在小根堆的最小值。数据保证该数未被删除。
4 x，删除第 x 个插入的数所在小根堆的最小值（若最小值不唯一，则优先删除先插入的数）。数据保证该数未被删除。
DSU+左偏树 DSU不支持删除，还要使用DSU的换根操作
同时维护DSU和左偏树的集合,每棵左偏树的root和DSU的root的编号是相同的，但是两者没有其他的联系*/
const int N = 200010; //假设所有操作都是增加节点 节点数量上界
int n; //操作数量
int v[N], dist[N], l[N], r[N], idx;
int p[N]; //DSU father
//双关键字排序，val相同比较编号
bool cmp(int x, int y) {
    if (v[x] != v[y]) return v[x] < v[y];
    return x < y;
}
int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}
//合并x为根的子树和y为根的子树 返回合并后的root节点编号
int merge(int x, int y) {
    if (!x || !y) return x + y; //空节点直接返回不空的那个
    if (cmp(y, x)) swap(x, y); //x是较小的点的编号
    r[x] = merge(r[x], y); //让x的右子树变为x的右子树和y合并之后的子树
    //回溯维护dist
    if (dist[r[x]] > dist[l[x]]) swap(l[x], r[x]); //维护左偏
    dist[x] = dist[r[x]] + 1;//每个节点dist为右儿子dist+1
    return x;
}
int main() {
    scanf("%d", &n);
    v[0] = 2e9; //边界0不会用到 x,y从1开始防止0变成root
    while (n --) {
        int t, x, y;
        scanf("%d%d", &t, &x);
        if (t == 1) {
            v[++idx] = x;
            dist[idx] = 1; //插入的时候要初始化该节点的dist 空节点dist从1开始
            p[idx] = idx;
        } else if (t == 2) {
            scanf("%d", &y);
            x = find(x), y = find(y);
            if (x != y) {
                if (cmp(y, x)) swap(x, y);
                p[y] = x;
                merge(x, y);
            }
        } else if (t == 3) {
            printf("%d\n", v[find(x)]);
        } else {
            x = find(x);
            if (cmp(r[x], l[x])) swap(l[x], r[x]);
            p[x] = l[x], p[l[x]] = l[x]; //并查集换根
            merge(l[x], r[x]);
        }
    }
    return 0;
}
/*Baltic2004《数字序列》：给定一个整数序列 a1,a2,...,an。求一个递增序列b1<b2<...<bn使得序列ai和bi的各项之差的绝对值之和 |a1−b1|+|a2−b2|+⋅⋅⋅+|an−bn| 最小。
第一行输出绝对值之和的最小值。第二行输出b1,b2,...,bn任意方案即可。此题的本质是“改变序列中的元素使其单调的最小代价”,就是求一些点和线性回归方程的差值。复杂度O(NlogN)*/
typedef long long ll;
const int N = 1000010;
int n;
int v[N], dist[N], l[N], r[N];
int ans[N];
struct Segment {
    int end, root, size;
} stk[N];
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (v[x] < v[y]) swap(x, y); //大根堆
    r[x] = merge(r[x], y);
    if (dist[r[x]] > dist[l[x]]) swap(r[x], l[x]);
    dist[x] = dist[r[x]] + 1;
    return x;
}
int pop(int x) {
    //合并左右子树 就相当于删掉root
    return merge(l[x], r[x]);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        v[i] -= i;
    }
    int tt = 0;
    for (int i = 1; i <= n; i++) {
        auto cur = Segment({i, i, 1});
        dist[i] = 1;
        while (tt && v[cur.root] < v[stk[tt].root]) {
            cur.root = merge(cur.root, stk[tt].root);
            if (cur.size % 2 && stk[tt].size % 2)
                cur.root = pop(cur.root);
            cur.size += stk[tt].size;
            tt --;
        }
        stk[++tt] = cur;
    }
    for (int i = 1, j = 1; i <= tt; i++) {
        while (j <= stk[i].end)
            ans[j++] = v[stk[i].root];
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) res += abs(v[i] - ans[i]);
    printf("%lld\n", res);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i] + i);
    return 0;
}
/*POJ3016《K-单调》：将长度为N的序列修改元素值使其为K段单调序列，求最小代价。
左偏树+DP,左偏树可以求出将一个序列单调的最少代价
此题是分段单调,cost[i][j]表示将下标i~j这一段单调需要的代价
f[i][j]表示将区间1~i的元素分成j段单调区间的代价 那么f[n][k]就是最终的答案
假设最后一段的长度是k，那么递推关系：f[i][j] = f[i-k][j-1] + cost[i-k+1][i]
将上升的v[i]取反之后相当于将坐标系沿x轴反转，此时的回归直线由单调上升变为单调下降，重新求一次即可,同时维护上升和下降序列二者之一最小值来更新答案。复杂度O(N^2logN)*/
const int N = 1010;
int n, m;
int f[N][11], cost[N][N];
int w[N], v[N], dist[N], l[N], r[N];
struct Segment {
    int root;
    int tot_sum, tot_size;
    int tree_sum, tree_size;
    int get_cost() { //求出当前段内全部改为中位数的花费
        int mid = v[root];
        return mid * tree_size - tree_sum + tot_sum - tree_sum - (tot_size - tree_size) * mid;
    }
} stk[N];
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (v[x] < v[y]) swap(x, y);
    r[x] = merge(r[x], y);
    if (dist[l[x]] < dist[r[x]]) swap(l[x], r[x]);
    dist[x] = dist[r[x]] + 1;
    return x;
}
int pop(int x) {
    return merge(l[x], r[x]);
}
void get_cost(int u) {
    int tt = 0, res = 0;
    for (int i = u; i <= n; i++) {
        auto  cur = Segment({i, v[i], 1, v[i], 1});
        l[i] = r[i] = 0, dist[i] = 1;
        while (tt && v[cur.root] < v[stk[tt].root]) {
            //先减去上一段，合并之后重新求一次
            res -= stk[tt].get_cost();
            cur.root = merge(cur.root, stk[tt].root);
            bool is_pop = cur.tot_size % 2 && stk[tt].tot_size % 2;
            cur.tot_size += stk[tt].tot_size;
            cur.tot_sum += stk[tt].tot_sum;
            cur.tree_size += stk[tt].tree_size;
            cur.tree_sum += stk[tt].tree_sum;
            if (is_pop) {  //2段都是奇数 弹出当前中位数
                cur.tree_size --;
                cur.tree_sum -= v[cur.root];
                cur.root = pop(cur.root);
            }
            tt --;
        }
        stk[++tt] = cur;
        res += cur.get_cost(); //重新求合并之后的段
        cost[u][i] = min(cost[u][i], res); //上升和下降求min
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)scanf("%d", &w[i]);
    memset(cost, 0x3f, sizeof cost);
    for (int i = 1; i <= n; i++) v[i] = w[i] - i;
    for (int i = 1; i <= n; i++) get_cost(i);
    //取反求单调下降的最少代价
    for (int i = 1; i <= n; i++) v[i] = -w[i] - i;
    for (int i = 1; i <= n; i++) get_cost(i);
    //DP
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) //枚举段数
            for (int k = 1; k <= i; k++) //最后一段的长度
                f[i][j] = min(f[i][j], f[i - k][j - 1] + cost[i - k + 1][i]);
    printf("%d\n", f[n][m]);
    return 0;
}
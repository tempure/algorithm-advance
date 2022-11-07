#include <bits/stdc++.h>
using namespace std;

/*
左偏树+DP 左偏树可以求出将一个序列单调的最少代价
此题是分段单调
cost[i][j]表示将下标i~j这一段单调需要的代价
f[i][j]表示将区间1~i的元素分成j段单调区间的代价 那么f[n][k]就是最终的答案
假设最后一段的长度是k，那么递推关系：f[i][j] = f[i-k][j-1] + cost[i-k+1][i]

注意此题的单调上升和下降都可以，此题的几何角度理解，就是求一些点和线性回归方程的残差的和
将上升的v[i]取反之后，相当于将整个坐标系沿x轴反转，此时的回归直线由单调上升变为单调下降，重新求一次即可
*/

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
            res -= stk[tt].get_cost();//先减去上一段，合并之后重新求一次
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
        cost[u][i] = min(cost[u][i], res); //单调上升还是下降求min的结果
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)scanf("%d", &w[i]);
    memset(cost, 0x3f, sizeof cost);
    for (int i = 1; i <= n; i++) v[i] = w[i] - i;
    for (int i = 1; i <= n; i++) get_cost(i);
    for (int i = 1; i <= n; i++) v[i] = -w[i] - i; //取反求单调下降的最少代价
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
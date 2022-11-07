/*
N个物品，背包体积W，每个物品体积G[i],求最多能装的体积
数据范围1<= N <=46,1 <= W,G[i] <= 2^31−1
第一行两个整数，W和N。以后N行，每行一个正整数表示G[i]
输出格式
仅一个整数，表示能装的最多的物品体积和
*/
/*
    可以看成01背包，但是背包复杂度N*V 用dp做会超时
    N比较小 所以考虑搜索 在所有方案里面找最大值
    预处理前K个物品，打表 排序 判重 改为双向DFS
    注意预处理不一定要均分，可以不均分
    后N - K 直接二分查前面的表 降为log复杂度查找 以及排序
    降序排序，优先搜索大数 贪心策略
    剪枝：不能超过上限W
*/
const int N = 46;
int n, m, k;
int w[N];
//  由于什么都不选 就是全0也是合法 weights[0]就是0 cnt从1开始
int weights[1 << 25], cnt = 1; //weights 所有能凑出来的重量
int ans; //答案
void dfs1(int u, int s) { //当前枚举到的数 当前的和
    if (u == k) {
        weights[cnt++] = s;
        return ;
    }
    dfs1(u + 1, s); //不选
    if (1ll * s + w[u] <= m) dfs1(u + 1, s + w[u]); //选
}
void dfs2(int u, int s) {
    if (u == n) {
        int l = 0, r = cnt - 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (weights[mid] <= m - s) l = mid;
            else r = mid - 1;
        }
        ans = max(ans, weights[l] + s);
        return ;
    }
    dfs2(u + 1, s);
    if (1ll * s + w[u] <= m) dfs2(u + 1, s + w[u]);
}
int main() {
    cin >> m >> n;
    for (int i = 0; i < n; i++) cin >> w[i];
    sort(w, w + n);
    reverse(w, w + n);
    k = n / 2 + 2; //前半段25 后半段21
    dfs1(0, 0);
    sort(weights, weights + cnt);
    // cnt = unique(weights, weights + cnt) - weights; //去重之后前一部分能组合出多少不同的重量
    dfs2(k, 0);
    cout << ans << endl;
    return 0;
}
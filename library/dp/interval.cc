/*
设有N堆石子排成一排，其编号为1，2，3，…，N。
每堆石子有一定的质量，可以用一个整数来描述，现在要将这N堆石子合并成为一堆。
每次只能合并相邻的两堆，合并的代价为这两堆石子的质量之和，合并后与这两堆石子相邻的石子将和新堆相邻，合并时由于选择的顺序不同，合并的总代价也不相同。
问题是：找出一种合理的方法，使总的代价最小，输出最小代价。
输入格式:第一行一个数N表示石子的堆数N。
第二行N个数，表示每堆石子的质量(均不超过1000)
*/
const int N = 1010;
int a[N], f[N][N];
int sum[N];
int main() {
    memset(f, 0x3f, sizeof f);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) { //前缀和
        f[i][i] = 0;
        sum[i] = sum[i - 1] + a[i];
    }
    for (int len = 2; len <= n; len++) //枚举阶段
        for (int l = 1; l + len - 1 <= n;  l++) {
            int r = l + len - 1;
            for (int k = l; k < r; k++)
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);  //只需要枚举k的位置 然后求出最小的分割
            f[l][r] += sum[r] - sum[l - 1]; //最后加上的前缀和 都是一样的 所以没必要在枚举k的时候加上
        }
    cout << f[1][n] << endl;
    return 0;
}
/*环形石子合并
将 n 堆石子绕圆形操场排放，现要将石子有序地合并成一堆。
规定每次只能选相邻的两堆合并成新的一堆，并将新的一堆的石子数记做该次合并的得分。
请编写一个程序，读入堆数 n 及每堆的石子数，并进行如下计算：
选择一种合并石子的方案，使得做 n−1 次合并得分总和最大。
选择一种合并石子的方案，使得做 n−1 次合并得分总和最小。
输入格式:第一行包含整数 n，表示共有 n 堆石子。
第二行包含 n 个整数，分别表示每堆石子的数量。
输出格式 输出共两行：
第一行为合并得分总和最小值，
第二行为合并得分总和最大值。
*/
const int N = 410; //开2倍的链长度
const int INF = 0x3f3f3f3f;
int n;
int s[N], w[N];
int f[N][N];  //最小值  f[i][j] 表示合并区间i~j所需要的最小值
int g[N][N];  // 最大值
//朴素的石子合并 一排的 复杂度是n^3
//环形的思路是枚举环上的缺口 然后再用朴素 这样本质是求n-1个 长度为n的链合并 复杂度n^4 要优化
//优化 直接把环形展开 复制一份 2个拼起来 一起 然后在2n长度区间 求区间长度为n的区间即可
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w[i + n] = w[i];
    }
    //前缀和
    for (int i = 1; i <= 2 * n; i++) s[i] = s[i - 1] + w[i];
    memset(f, 0x3f, sizeof f);
    memset(g, 0xcf, sizeof g);
    for (int len = 1; len <= n; len ++) //区间长度
        for (int l = 1; l + len - 1 <= n * 2; l++) { //左端点
            int r = l + len - 1; //右端点
            if (len == 1) f[l][r] = g[l][r] = 0;
            else {
                for (int k = l; k < r; k++) { //分界点
                    f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
                    g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r] + s[r] - s[l - 1]);
                }
            }
        }
    int minv = INF, maxv = -INF;
    //由于是2倍的长度 所以要遍历一次 求出最值
    for (int i = 1; i <= n; i++) {
        minv = min(minv, f[i][i + n - 1]);
        maxv = max(maxv, g[i][i + n - 1]);
    }
    cout << minv << endl << maxv << endl;
    return 0;
}
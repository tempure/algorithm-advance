/*
有 N 件物品和一个容量是 V 的背包。每件物品只能使用一次。
第 i 件物品的体积是 vi，价值是 wi。
求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
输出 最优选法的方案数。输出答案模 109+7 的结果。
输入格式
第一行两个整数，N，V，用空格隔开，分别表示物品数量和背包容积。
接下来有 N 行，每行两个整数 vi,wi，用空格隔开，分别表示第 i 件物品的体积和价值。
输出格式:输出一个整数，表示方案数模 1e9+7 的结果。
数据范围
0 <= N,V <= 1000
0 <= vi,wi <= 1000
*/
const int N = 1010, mod = 1e9 + 7;
int f[N], g[N];  //g数组记录f[]取到最大 时候的方案数
int n, m;
int main() {
    cin >> n >> m;
    memset(f, 0xcf, sizeof f);
    f[0] = 0;
    g[0] = 1;
    for (int i = 0; i < n; i++) {
        int v, w;
        cin >> v >> w;
        for (int j = m; j >= v; j--) {
            int maxv = max(f[j], f[j - v] + w);
            int cnt = 0;
            if (maxv == f[j]) cnt += g[j]; //不选第i个物品的最优方案数
            if (maxv == f[j - v] + w) cnt += g[j - v]; //选第i个物品的最优方案数
            g[j] = cnt % mod;
            f[j] = maxv;
        }
    }
    int res = 0;
    for (int i = 0; i <= m; i++) res = max(res, f[i]);
    int cnt = 0; //找出最大的方案数 求和
    for (int i = 0; i <= m; i++)
        if (res == f[i]) cnt = (cnt + g[i]) % mod;
    cout << cnt << endl;
    return 0;
}
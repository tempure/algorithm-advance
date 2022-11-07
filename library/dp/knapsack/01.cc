/*
有 N 件物品和一个容量是V的背包。每件物品只能使用一次。
第 i 件物品的体积是vi价值是 wi。
求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
输出最大价值。 复杂度O(N * V)
*/
const int N = 1010;
int n, m;   //m表示背包的容积
int v[N], w[N];
int f[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];
    for (int i = 1; i <= n; i++)
        //这里的j <= m  就保证了决策的边界 一定不会超出背包容积
        for (int j = m; j >= v[i]; j--) {

            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    cout << f[m] << endl;
    return 0;
}
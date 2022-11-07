/*
一个正整数n可以表示成若干个正整数之和，形如：n=n1+n2+…+nk，其中n1≥n2≥…≥nk,k≥1。
我们将这样的一种表示称为正整数n的一种划分。
现在给定一个正整数n，请你求出n共有多少种不同的划分方法。
输入格式:共一行，包含一个整数n。
输出格式
共一行，包含一个整数，表示总划分数量。
由于答案可能很大，输出结果请对109+7取模。
*/
const int N = 1010, M = 1e9 + 7;
//整数划分 第二种 思路；
//f[i][j]表示总和是i用了j个数加起来得到了N 的所有方案数
//分为两类 一种是 这j个数 中最小值是1， 另外一种是 最小值大于1
// f[i][j] = f[i - 1][j-1] + f[i - j][j]  第一项是把开头的1去掉 第二项是 j个数 每个都减去1
//最后的答案 ans = f[n][1] + f[n][2] + ..... f[n][n]
int n;
int f[N][N];
int main() {
    cin >> n;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            f[i][j] = (f[i - 1][j - 1] + f[i - j][j]) % M;
    int res = 0;
    for (int i = 1; i <= n; i++) res = (res + f[n][i]) % M;
    cout << res  << endl;
    return 0;
}


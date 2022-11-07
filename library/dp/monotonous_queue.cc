/*
输入一个长度为n的整数序列，从中找出一段长度不超过m的连续子序列，使得子序列中所有数的和最大。
注意： 子序列的长度至少是1。
输入格式:第一行输入两个整数n,m。
第二行输入n个数，代表长度为n的整数序列。
同一行数之间用空格隔开。
输出格式
输出一个整数，代表该序列的最大子序和。
*/
//滑动窗口
const int N = 300010;
int q[N];  //单调队列下标
ll s[N]; //前缀和
int n, m;
//对于单调队列的下标问题：
//如果是从0开始写的代码，那么i就是窗口的最后一个元素 则判断条件是i - q[hh] + 1 > m
//就要hh++ 对于本题 下标从1开始，窗口的结尾元素下标是i - 1, 而i是窗口后的一个元素
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++ ) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    int hh = 1, tt = 1;  //队头 队尾
    ll res = INT_MIN;
    for (int i = 1; i <= n; i++) {
        if (i - q[hh] > m) hh++;
        res = max(res, s[i] - s[q[hh]]);
        while (hh <= tt && s[q[tt]] >= s[i]) tt--;
        q[++tt] = i; //队尾下标
    }
    cout << res << endl;
    return 0;
}
/*
烽火台是重要的军事防御设施，一般建在交通要道或险要处。
一旦有军情发生，则白天用浓烟，晚上有火光传递军情。
在某两个城市之间有 n 座烽火台，每个烽火台发出信号都有一定的代价。
为了使情报准确传递，在连续 m 个烽火台中至少要有一个发出信号。
现在输入 n,m 和每个烽火台的代价，请计算在两城市之间准确传递情报所需花费的总代价最少为多少。
输入格式:第一行是两个整数 n,m，具体含义见题目描述；
第二行 n 个整数表示每个烽火台的代价 ai
输出格式:输出仅一个整数，表示最小代价
*/
const int N = 200010;
int w[N], f[N], q[N];
int n, m;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    int hh = 0, tt = 0;
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (q[hh] < i - m) hh ++;
        f[i] = f[q[hh]] + w[i];
        while (hh <= tt && f[q[tt]] > f[i]) tt--;
        q[++tt] = i;
    }
    int res = 1e9;
    for (int i = n - m + 1; i <= n; i++) res = min(res, f[i]);
    cout << res << endl;
    return 0;
}
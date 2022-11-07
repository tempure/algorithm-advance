/*
    双指针算法：
    常见问题分类：
    (1) 对于一个序列，用两个指针维护一段区间
    (2) 对于两个序列，维护某种次序，比如归并排序中合并两个有序序列的操作
*/
for (int i = 0, j = 0; i < n; i ++ ) {
    while (j < i && check(i, j)) j ++ ;
    // 具体问题的逻辑
}
/*
    例题：最长连续不重复子序列
    给定一个长度为n的整数序列，请找出最长的不包含重复的数的连续区间，输出它的长度。
*/
const int N = 100010;
int a[N], s[N];
int n;
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int res = 0;
    for (int i = 0, j = 0; i < n; i++) {
        s[a[i]]++;
        while (s[a[i]] > 1) {
            s[a[j]] -- ;
            j++;   // j 跳到下一个元素，直到当前区间没有重复元素
        }
        res = max(res, i - j + 1);
    }
    printf("%d", res);
    return 0;
}
/*
    例题：数组元素的目标和
    给定两个升序排序的有序数组A和B，以及一个目标值x。数组下标从0开始。
    请你求出满足A[i] + B[j] = x的数对(i, j)。
    数据保证有唯一解。第一行包含三个整数n，m，x，分别表示A的长度，B的长度以及目标值x。
    第二行包含n个整数，表示数组A。 第三行包含m个整数，表示数组B。
*/
const int N = 100010;
int a[N], b[N];
int n, m, x;
int main() {
    cin >> n >> m >> x;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    for (int i = 0, j = m - 1; i < n; i++) {
        while (j >= 0 && a[i] + b[j] > x) j--;
        if (j >= 0 && a[i] + b[j] == x) cout << i << ' ' << j << endl;
    }
    return 0;
}

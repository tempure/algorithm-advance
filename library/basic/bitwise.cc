/*
    求n的第k位数字: n >> k & 1
    返回n的最后一位1：lowbit(n) = n & -n
*/
/*
    例题:二进制中1的个数
    给定一个长度为n的数列，请你求出数列中每个数的二进制表示中1的个数。
    1 <= n <= 100000, 0 <= 数列中元素的值 <= 1e9
*/
const int N  = 100010;
int a[N];
int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        while (a[i]) {
            a[i] -= a[i] & -1 * a[i];
            cnt++;
        }
        printf("%d ", cnt);
    }
}

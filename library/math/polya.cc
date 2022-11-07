/*POJ2409:给定 M 种不同颜色的珠子，每种颜色的珠子的个数都足够多。现在要从中挑选 N 个珠子，串成一个环形手链。请问一共可以制作出多少种不同的手链。注意，如果两个手链经旋转或翻转后能够完全重合在一起，对应位置的珠子颜色完全相同，则视为同一种手链*/
typedef long long ll;
int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
int main() {
    int m, n;
    while (cin >> m >> n, m || n) {
        ll res = 0;
        for (int i = 0; i < n; i++)
            res += power(m, __gcd(n, i)); //旋转
        //翻转
        if (n % 2) res += n * power(m, (n + 1) / 2); //奇数
        else
            res += n / 2 * (power(m, n / 2 + 1) + power(m, n / 2)); //偶数
        cout << res / n / 2 << endl;
    }
    return 0;
}
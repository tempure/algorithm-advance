#include <iostream>
using namespace std;

/*
有一定思维难度，首先要想到用二分，二分不一定要满足单调性，凡是求最值，都可以用二分尝试
每次二分中位数的可能值，然后在序列中全部减去该中位数，再求一个前缀和
因为要求的是区间长度至少为f，维护一个长度至少是f的区间，用双指针维护
假设区间末尾是j，开头是i，那么每次向右移动过程更新s[0]~s[j-f]中的最小值 minv
如果存在一个s[j] - minv >= 0 说明存在一个区间长度>=f 而且平均值大于当前二分的平均值
因为如果平均值恰好等于当前二分的平均值，那么序列每个元素减去后，总和一定为0
*/

const int N = 1e5 + 10;
int a[N];
double s[N]; //前缀和数组

int n, f;

bool check(double avg) {
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i] - avg;
    double minv = 0;
    for (int i = 0, j = f; j <= n; i++, j++) {
        minv = min(minv, s[i]);
        if (s[j] >= minv) return true;
    }
    return false;
}

int main() {
    cin >> n >> f;
    for (int i = 1; i <= n; i++) cin >> a[i];
    double l = 0, r = 2000;
    while (r - l > 1e-5) { //题目本质是保留三位小数的精度，那么取1e-5精度即可
        double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    //注意一定要输出r*1000，其实本质就是要保留三位小数
    //如果输出l，因为是浮点数二分，假设l是浮点数，r恰好是一个整数
    //l=6499.999999, r = 6500,那么取l就会错,如果r是一个差距<1e-5的浮点数，则取整后不会错
    cout << (int)(r * 1000) << endl;

    return 0;
}
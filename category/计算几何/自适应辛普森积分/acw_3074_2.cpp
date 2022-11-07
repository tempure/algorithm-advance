#include <bits/stdc++.h>
using namespace std;

/*
核心思路：使用二次函数积分微元面积来近似
递归区间，假设整个区间面积为S，然后按照横坐标一半平均划分为左右部分
如果 fabs(S左+S右-S) < eps 直接return即可，否则继续递归
*/

const double eps = 1e-12;

double f(double x) {  //模板唯一需要修改的函数，eps一般不改
    return sin(x) / x;
}

double simpson(double l, double r) {
    auto mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6; //近似为二次函数的面积
}

double asr(double l, double r, double s) {
    auto mid = (l + r) / 2;
    auto left = simpson(l, mid), right = simpson(mid, r);
    if (fabs(left + right - s) < eps) return left + right;
    return asr(l, mid, left) + asr(mid, r, right);
}

int main() {
    double l, r;
    scanf("%lf%lf", &l, &r);
    printf("%lf\n", asr(l, r, simpson(l, r)));
    return 0;
}
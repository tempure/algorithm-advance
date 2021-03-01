#include <bits/stdc++.h>
using namespace std;

/*
simpson积分模板
用二次函数来代替矩形的区间微分法来积分

找三个点(a,f(a)) (b,f(b)) ((a+b)/2, f((a+b)/2)) 来求出一个二次函数表达式
[a,b]之间的面积就是 (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6
*/

const double eps = 1e-12;

double f(double x) { //要求的积分函数
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
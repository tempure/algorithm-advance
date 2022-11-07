#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

/*
辛普森积分求圆面积并：
函数f(x)为直线x和所有圆交线的长度并
用勾股定理计算直线和圆的交线段长
*/

typedef pair<double, double> pdd;
const int N = 1010;
const double eps = 1e-8;

int n;
struct Circle {
    pdd r;
    double R;
} c[N];
pdd q[N];

int dcmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

double f(double x) { //横坐标坐标为x的直线和所有圆交线的长度并
    int cnt =  0;
    for (int i = 0; i < n; i++) {
        auto X = fabs(x - c[i].r.x), R = c[i].R; //X是直线到圆心的距离
        if (dcmp(X, R) < 0) {
            auto Y = sqrt(R * R - X * X);
            q[cnt++] = {c[i].r.y - Y, c[i].r.y + Y}; //先加小的端点
        }
    }
    if (!cnt) return 0;
    sort(q, q + cnt);

    //合并区间
    double res = 0, st = q[0].x, ed = q[0].y;
    for (int i = 1; i < cnt; i++)
        if (q[i].x <= ed) ed = max(ed, q[i].y);
        else {
            res += ed - st;
            st = q[i].x, ed = q[i].y;
        }
    res += ed - st; //最后一个区间

    return res;
}

double simpson(double l, double r) {
    auto mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;
}

double asr(double l, double r, double s) {
    auto mid = (l + r) / 2;
    auto left = simpson(l, mid), right = simpson(mid, r);
    if (fabs(s - left - right) < eps) return left + right;
    return asr(l, mid, left) + asr(mid, r, right);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf%lf", &c[i].r.x, &c[i].r.y, &c[i].R);
    double l = -2000, r = 2000; //左右界 圆心+半径
    printf("%.3lf\n", asr(l, r, simpson(l, r)));

    return 0;
}
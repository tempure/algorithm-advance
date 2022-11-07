#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const double eps = 1e-8;

//两个点重合就随便输出一个圆就行
//如果点在圆外，就直接输出给出的圆就行了，最大
//如果点在圆内就和圆心连线，然后方向用向量求，向量做法涉及到的精度问题比较少

int cmp(double x, double y)
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

int main()
{
    double r, x1, y1, x2, y2;
    scanf("%lf%lf%lf%lf%lf", &r, &x1, &y1, &x2, &y2);
    double dx = x1 - x2;
    double dy = y1 - y2;
    double d = sqrt(dx * dx + dy * dy);
    if (cmp(d, r) >= 0) printf("%lf %lf %lf\n", x1, y1, r); //点在圆外
    else
    {
        if (!cmp(x1, x2) && !cmp(y1, y2)) //给出的点和圆心重合
            printf("%lf %lf %lf\n", x1 + r / 2, y1, r / 2);
        else
        {
            double r2 = (r + d) / 2;
            double x = x2 + (x1 - x2) / d * r2; //单位向量
            double y = y2 + (y1 - y2) / d * r2;
            printf("%lf %lf %lf\n", x, y, r2);
        }
    }

    return 0;
}
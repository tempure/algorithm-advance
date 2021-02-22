#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

/*
就是判断是否存在一条直线和所有线段都有交点

枚举所有不同线段的端点的连线来代替一条直线 这里的代替不能完全代替 毕竟线段有长度 所以要将这个代替的线段作为跨立实验的界限
枚举端点连线的思维本质上就是极限思维，因为如果端点连线的直线能和所有线段相交，那么介于端点之间的2点连线肯定和其他线段都相交


每次枚举点对的直线，然后枚举所有线段做跨立实验 复杂度O(T*n^3)
*/

typedef pair<double, double> pdd;
const int N = 210;  //一条线段2个端点 开2倍点
const double eps = 1e-8;

int n;
pdd q[N], a[N], b[N]; //q所有的点 a[],b[]所有线段的2个端点


int sign(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

int cmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}

double area(pdd a, pdd b, pdd c) { //计算向量ab和ac有向叉积面积
    return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

bool check() {
    for (int i = 0; i < n * 2; i++)
        for (int j = i + 1; j < n * 2; j++) { //枚举所有点对
            //不是同一个线段的2个端点才继续
            if (!cmp(q[i].x, q[j].x) && !cmp(q[i].y, q[j].y)) continue;
            bool flag = true;
            for (int k = 0; k < n; k++) //枚举所有线段
                //此处为了提高精度 ，先求出叉积正负再乘 而不是乘完再求正负
                //☠注意：此处判断直线和线段相交，一定要将直线作为跨立实验的界限
                //因为直线是无穷长的，但是线段长度有限，此处用2线段的端点连线的向量代替了直线
                //如果将被判断线段作为界限，用代替的直线来横跨就错了，因为本质上还是用一段线段来代替的直线
                //作为界限的线段，即使是一段向量，也不会出错，因为只会用到方向
                if (sign(area(q[i], q[j], a[k])) * sign(area(q[i], q[j], b[k])) > 0) {
                    flag = false;
                    break;
                }
            if (flag) return true;
        }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T --) {
        scanf("%d", &n);
        for (int i = 0, k = 0; i < n;  i++) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            q[k++] = {x1, y1}, q[k++] = {x2, y2};
            a[i] = {x1, y1}, b[i] = {x2, y2};
        }
        if (check()) puts("Yes!");
        else puts("No!");
    }
    return 0;
}
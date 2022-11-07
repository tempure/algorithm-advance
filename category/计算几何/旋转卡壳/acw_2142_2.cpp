/*
题目满足不共线所有点，输入点坐标都是浮点数

最小矩形覆盖一定唯一，注意题目要求输出点坐标的顺序

定理：最小矩形覆盖的一条边一定和凸包轮廓的一条边重合

旋转卡壳O(N), 凸包O(NlogN) 总复杂度O(NlogN)
*/

#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef pair<double, double> pdd;

const int N = 50010; //开总点数即可
const double eps = 1e-12, INF = 1e20;
const double PI = acos(-1);

int n;
pdd q[N];
pdd ans[N]; //每次旋转卡壳后的矩形的四个顶点
double min_area = INF;
int stk[N], top;
bool used[N];

int sign(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return  -1;
    return 1;
}

int dcmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

pdd operator+ (pdd a, pdd b) {
    return {a.x + b.x, a.y + b.y};
}

pdd operator- (pdd a, pdd b) {
    return {a.x - b.x, a.y - b.y};
}

pdd operator* (pdd a, double t) {
    return {a.x * t, a.y * t};
}

pdd operator/ (pdd a, double t) {
    return {a.x / t, a.y / t};
}

double operator* (pdd a, pdd b) {
    return a.x * b.y - a.y * b.x;
}

double operator&(pdd a, pdd b) {
    return a.x * b.x + a.y * b.y;
}

double area(pdd a, pdd b, pdd c) {
    return (b - a) * (c - a);
}

double get_len(pdd a) {
    return sqrt(a & a);
}

double project(pdd a, pdd b, pdd c) { //ac在ab上的投影 有正负之分
    return ((b - a) & (c - a)) / get_len(b - a);
}

pdd norm(pdd a) { //得到a的单位向量
    return a / get_len(a);
}

pdd rotate(pdd a, double b) {
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}

//旋转卡壳凸包模板
void get_convex() {
    sort(q, q + n);
    for (int i = 0; i < n; i++) { //下凸壳
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) <= 0) {
            // 凸包边界上的点即使被从栈中删掉，也不能删掉used上的标记
            if (area(q[stk[top - 2]], q[stk[top - 1]], q[i]) < 0)
                used[stk[--top]] = false;
            else top --;
        }
        stk[top++] = i; //栈顶下标从0开始
        used[i] = true;
    }

    //将起点再一次入栈
    used[0] = false;
    for (int i = n - 1; i >= 0; i--) { //求上凸壳
        if (used[i]) continue;
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) <= 0)
            top -- ;
        stk[top++] = i;
    }
    top --; //将栈顶后移 栈内删除0号元素 但是stk数组中还是存在0的 只不过top没指向
}

void rotating_calipers() {
    for (int i = 0, a = 2, b = 2, c = 2; i < top; i ++ ) {
        auto d = q[stk[i]], e = q[stk[i + 1]];
        while (dcmp(area(d, e, q[stk[a]]), area(d, e, q[stk[a + 1]])) < 0) a = (a + 1) % top;
        while (dcmp(project(d, e, q[stk[b]]), project(d, e, q[stk[b + 1]])) < 0) b = (b + 1) % top;
        if (!i) c = a;
        while (dcmp(project(d, e, q[stk[c]]), project(d, e, q[stk[c + 1]])) > 0) c = (c + 1) % top;
        auto x = q[stk[a]], y = q[stk[b]], z = q[stk[c]];
        auto h = area(d, e, x) / get_len(e - d);
        auto w = ((y - z) & (e - d)) / get_len(e - d);
        if (h * w < min_area) {
            min_area = h * w;
            ans[0] = d + norm(e - d) * project(d, e, y);
            ans[3] = d + norm(e - d) * project(d, e, z);
            auto u = norm(rotate(e - d, -PI / 2));
            ans[1] = ans[0] + u * h;
            ans[2] = ans[3] + u * h;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf%lf", &q[i].x, &q[i].y);
    get_convex();
    rotating_calipers();

    int k = 0;
    for (int i = 1; i < 4; i++) //找到第一个输出的点 最靠左下的一个
        if (dcmp(ans[i].y, ans[k].y) < 0 || !dcmp(ans[i].y, ans[k].y) && dcmp(ans[i].x, ans[k].x) < 0)
            k = i;

    if (!sign(min_area)) min_area = 0;
    printf("%.5lf\n", min_area);

    for (int i = 0; i < 4 ; i++, k++) {
        auto x = ans[k % 4].x, y = ans[k % 4].y;
        if (!sign(x)) x = 0; //防止出现小数点截断后 -0.00000
        if (!sign(y)) y = 0;
        printf("%.5lf %.5lf\n", x, y);
    }
    return 0;
}
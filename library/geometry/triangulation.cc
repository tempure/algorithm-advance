//POJ3675:求N个顶点的多边形和圆的面积交
/*三角剖分然后求出每个三角形和圆的交集面积求和即可
三角形和圆的位置关系 分5种讨论*/
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef pair<double, double> pdd;
const int N = 55;
const double eps = 1e-8; //-12会错
const double PI = acos(-1);
double R;
int n;
pdd q[N], r;
int sign(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
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
    return {a.x * b.y - a.y * b.x};
}
double operator& (pdd a, pdd b) {
    return {a.x * b.x + a.y * b.y};
}
double area(pdd a, pdd b, pdd c) {
    return (b - a) * (c - a);
}
double get_len(pdd a) {
    return sqrt(a & a);
}
double get_dist(pdd a, pdd b) {
    return get_len(b - a);
}
double project(pdd a, pdd b, pdd c) { //ac在ab上的投影
    return ((c - a) & (b - a)) / get_len(b - a);
}
pdd rotate(pdd a, double b) {
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}
pdd norm(pdd a) { //单位向量
    return a / get_len(a);
}
bool on_segment(pdd p, pdd a, pdd b) { //p点是否在线段ab内
    return !sign((p - a) * (p - b)) && sign((p - a) & (p - b)) <= 0;
}
pdd get_line_intersection(pdd p, pdd v, pdd q, pdd w) {
    auto u = p - q;
    auto t = w * u / (v * w);
    return p + v * t;
}
//求出直线ab和圆的交点，保存在pa和pb中
double get_circle_line_intersecion(pdd a, pdd  b, pdd &pa, pdd &pb) {
    //e是r向ab作垂线的垂足
    auto e = get_line_intersection(a, b - a,  r, rotate(b - a, PI / 2));
    auto mind = get_dist(r, e); //r到线段ab的最短距离 初始为r到垂足的距离
    //e不在ab中间 就返回到ab较小的一个
    if (!on_segment(e, a, b)) mind = min(get_dist(r, a), get_dist(r, b));
    if (dcmp(R, mind) <= 0) return mind; //线段ab和圆没有交点
    //线段ab和圆有交点
    auto len = sqrt(R * R - get_dist(r, e) * get_dist(r, e));
    pa = e + norm(a - b) * len;
    pb = e + norm(b - a) * len;
    return mind;
}
double get_sector(pdd a, pdd b) { //射线ra rb与圆心围成的扇形的面积
    auto angle = acos((a & b) / get_len(a) / get_len(b));
    if (sign(a * b) < 0) angle = -angle; //有向面积
    return R * R * angle / 2;
}
//求出r a b三角形和圆的交集面积
double get_circle_triangle_area(pdd a, pdd b) {
    auto da = get_dist(r, a), db = get_dist(r, b); //ra rb长度
    //ab都在圆内 直接返回三角形面积
    if (dcmp(R, da) >= 0 && dcmp(R, db) >= 0) return a * b / 2;
    if (!sign(a * b)) return 0; //ab共线 r为原点 面积为0
    pdd pa, pb;
    auto mind = get_circle_line_intersecion(a, b, pa, pb);
    //ab都在圆外 返回扇形面积
    if (dcmp(R, mind) <= 0) return get_sector(a, b);
    //ab中的一个在内 或者ab和圆有2个交点
    //a在内 b在外
    if (dcmp(R, da) >= 0) return a * pb / 2 + get_sector(pb, b);
    //a在外 b在内
    if (dcmp(R, db) >= 0) return get_sector(a, pa) + pa * b / 2;
    //ab都在外 但是穿过圆
    return get_sector(a, pa) + pa * pb / 2 + get_sector(pb, b);
}
double work() {
    double res = 0;
    for (int i = 0; i < n; i++)
        res += get_circle_triangle_area(q[i], q[(i + 1) % n]);
    return fabs(res);
}
int main() {
    while (scanf("%lf%d", &R, &n) != - 1) {
        for (int i = 0; i < n; i++) scanf("%lf%lf", &q[i].x, &q[i].y);
        printf("%.2lf\n", work());
    }
    return 0;
}
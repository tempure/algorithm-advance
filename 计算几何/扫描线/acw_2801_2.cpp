#include <bits/stdc++.h>
using namespace std;

#define x  first
#define y second

/*
求所有三角形的面积并

和矩形不一样，矩形是所有的顶点横坐标作为分界线
三角形除了顶点之外，还要将所有边的交点也作为分界线，分解区间内的就是梯形或者平行四边形了
只需要求出每个区间左右2条线上的交点区间长度并，用梯形面积公式计算即可(梯形面积公式适用于平行四边形)
*/

typedef pair<double, double> pdd;
const int N = 110;
const double eps = 1e-8, INF = 1e9;

int n;
pdd tr[N][3]; //所有三角形的三个点
pdd q[N]; //所有三角形和划分边界的交点的纵坐标的区间

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

double operator* (pdd a, pdd b) {
    return {a.x * b.y - a.y * b.x};
}

double operator& (pdd a, pdd b) {
    return a.x * b.x + a.y * b.y;
}

//判断p点是否在线段ab上 p已经和ab共线
bool on_segment(pdd p, pdd a, pdd b) {
    return sign((p - a) & (p - b)) <= 0;
}

//求出线段pv和qw的交点 v和w是方向向量
pdd get_line_intersection(pdd p, pdd v, pdd q, pdd w) {
    if (!sign(v * w)) return {INF, INF}; //共线特判
    auto u = p - q;
    auto t = w * u / (v * w);
    auto o = p + v * t;
    //由于是线段不是直线 所以特判
    if (!on_segment(o, p, p + v) || !on_segment(o, q, q + w))
        return {INF, INF};
    return o;
}

double line_area(double a, int side) { //处理区间的一侧
    int cnt = 0; //纵向需要合并的区间的个数
    for (int i = 0; i < n; i++) { //枚举所有的三角形 此时三个点的横坐标都是升序的
        auto t = tr[i];
        if (dcmp(t[0].x, a) > 0 || dcmp(t[2].x, a) < 0) continue;  //只处理横跨当前区间的 区间内的不要

        //特判三角形一条边和区间划分的直线共线
        if (!dcmp(t[0].x, a) && !dcmp(t[1].x, a)) {
            //和左侧共线
            if (side) q[cnt++] = {t[0].y, t[1].y};
        }
        else if (!dcmp(t[2].x, a) && !dcmp(t[1].x, a)) {
            //和右侧共线
            if (!side) q[cnt++] = {t[2].y, t[1].y};
        }
        else { //没有和边界共线的情况，就是直接横跨
            double d[3]; //存储三角形的三条边和边界a的交点 最多3个，就是2条边交点在边界线的情况
            int u = 0;
            for (int j = 0; j < 3; j++) {
                //求出和边界线a的交点 用无穷来表示直线及其方向向量
                auto o = get_line_intersection(t[j], t[(j + 1) % 3] - t[j], {a, -INF}, {0, INF * 2});
                if (dcmp(o.x, INF))
                    d[u++] = o.y;
            }
            if (u) {
                sort(d, d + u);
                q[cnt++] = {d[0], d[u - 1]};
            }
        }
    }
    if (!cnt) return 0;
    /*
    注意：下面swap的目的是，在三角形一条边和边界a共线的情况，两个端点的纵坐标不一定是有序的
    所以要swap，后面普通的非共线情况是已经排序的，此处只处理共线的情况。

    也可以将上边共线的情况加入q[]写为：
    if (side) q[cnt++] = {min(t[0].y, t[1].y), max(t[0].y, t[1].y)};
    if (!side) q[cnt++] = {min(t[2].y, t[1].y), max(t[2].y, t[1].y)};
    从而不用最后扫一遍swap，也能过
    */
    for (int i = 0; i < cnt; i++)
        if (q[i].x > q[i].y)
            swap(q[i].x, q[i].y); //pair双关键字排序 确保区间的端点有序
    sort(q, q + cnt);

    //区间合并
    double res = 0, st = q[0].x, ed = q[0].y;
    for (int i = 1; i < cnt; i++)
        if (q[i].x <= ed) ed = max(ed, q[i].y);
        else {
            res += ed - st;
            st = q[i].x, ed = q[i].y;
        }
    res += ed - st; //加上最后一个区间
    return res;
}

double range_area(double a, double b) {
    //a的右侧和b的左侧 1为右侧
    //三角形和矩形不一样，每条区间的线要单独处理左侧和右侧
    return (line_area(a, 1) + line_area(b, 0)) * (b - a) / 2;
}

int main() {
    scanf("%d", &n);
    vector<double> xs;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%lf%lf", &tr[i][j].x, &tr[i][j].y);
            xs.push_back(tr[i][j].x); //存入所有三角形的顶点横坐标
        }
        sort(tr[i], tr[i] + 3); //每个三角形的横坐标排序
    }
    //求出所有三角形的所有边的交点
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++) {
                    auto o = get_line_intersection(tr[i][x], tr[i][(x + 1) % 3] - tr[i][x],
                                                   tr[j][y], tr[j][(y + 1) % 3] - tr[j][y]);
                    if (dcmp(o.x, INF))
                        xs.push_back(o.x);
                }
    sort(xs.begin(), xs.end());
    double res = 0;
    for (int i = 0; i + 1 < xs.size(); i++)
        if (dcmp(xs[i], xs[i + 1]))
            res += range_area(xs[i], xs[i + 1]);
    printf("%.2lf\n", res);

    return 0;
}
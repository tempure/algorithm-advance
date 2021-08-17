#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using pdd = pair<double, double>;

/*
几点注意事项：
q[]队列里面存的是边的编号

S&I 算法每次都要先更新队尾，后更新队头的解释：
对于假如一个新的边，能把所有边都弹出去的特殊情况，参考oi-wiki的三条边的特殊情况
这样如果先更新队头，那么就把第一条加的边删掉了，这样就留下了后加入的两条边
此时hh+1=tt,队中只有两条边，停止更新了

如果先更新队尾，那么就留下了第一条和第三条边，这才是正确的直线平面交集
*/

const int N = 510;
const double eps = 1e-8;

struct Line {
    pdd st, ed;
} line[N];

int cnt; //边数
pdd pg[N], intersec[N];
int q[N];

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

double get_angle(const Line & a) {
    return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x);
}

pdd operator-(pdd a, pdd b) {
    return{a.x - b.x, a.y - b.y};
}

double cross(pdd a, pdd b) {
    return a.x * b.y - a.y * b.x;
}

double area(pdd a, pdd b, pdd c) {
    return cross(b - a, c - a);
}

bool cmp(const Line &a, const Line &b) {
    double A = get_angle(a), B = get_angle(b);
    if (!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0;
    return A < B;
}

pdd get_line_intersection(pdd p, pdd v, pdd q, pdd w) {
    auto u = p - q;
    double t = cross(w, u) / cross(v, w);
    return {p.x + v.x * t, p.y + v.y * t};
}

pdd get_line_intersection(Line &a, Line &b) {
    return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}

bool on_right(Line &a, Line &b, Line &c) {
    auto o = get_line_intersection(b, c);
    return sign(area(a.st, a.ed, o)) <= 0;
}

//半平面交
double half_plane_intersection() {
    sort(line, line + cnt, cmp);
    int hh = 0, tt = -1;
    for (int i = 0; i < cnt; i++) {
        //遇到平行且靠右的直线 直接跳过
        if (i && !dcmp(get_angle(line[i]), get_angle(line[i - 1]))) continue;
        //一定要先更新队尾 h+1<=tt保证队列至少有2条边
        while (hh + 1 <= tt && on_right(line[i], line[q[tt - 1]], line[q[tt]])) tt --;
        while (hh + 1 <= tt && on_right(line[i], line[q[hh]], line[q[hh + 1]])) hh ++;
        q[++tt] = i;
    }
    //队头更新队尾 队尾更新队头
    while (hh + 1 <= tt && on_right(line[q[hh]], line[q[tt - 1]], line[q[tt]])) tt --;
    while (hh + 1 <= tt && on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]])) hh ++;

    q[++tt] = q[hh]; //队头复制一份加到队尾 得以求出队尾和队头边的交点
    int k = 0;
    for (int i = hh; i < tt; i++) //所有交点就是轮廓
        intersec[k++] = get_line_intersection(line[q[i]], line[q[i + 1]]);

    double res = 0;
    for (int i = 1; i + 1 < k; i++) //三角剖分求多边形面积 第一个点作为旋转扫描的点
        res += area(intersec[0], intersec[i], intersec[i + 1]);
    return res / 2;
}

void solve() {
    int n, m;
    cin >> n;
    while (n --) {
        cin >> m;
        for (int i = 0; i < m; i++) cin >> pg[i].x >> pg[i].y;
        for (int i = 0; i < m; i++)
            line[cnt++] = {pg[i], pg[(i + 1) % m]};
    }
    double res = half_plane_intersection();
    printf("%.3lf\n", res);
}

int main() {
    solve();
    return 0;
}
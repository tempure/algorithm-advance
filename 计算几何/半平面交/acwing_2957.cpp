#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long double ld; //此题精度要求很高 用long double
typedef pair<int, int> pii;
typedef pair<ld, ld> pdd;

const int N = 10010;
const ld eps = 1e-18; //数据范围1e9 精度直接-18

int n, cnt;
struct Line {
    pdd st, ed;
    vector<int> ids; //重合的所有直线
} line[N];

int ki[N], vi[N]; //截距和速度
int q[N], ans[N];

int sign(ld x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

int dcmp(ld x, ld y) {
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

ld get_angle(const Line &a) {  //得到一条直线的极角反正切值
    //反三角函数也是单调递增的 所以可以用来排序
    return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x);
}

pdd operator-(pdd a, pdd b) {
    return {a.x - b.x, a.y - b.y};
}

ld cross(pdd a, pdd b) {
    return a.x * b.y - a.y * b.x;
}

ld area(pdd a, pdd b, pdd c) {
    return cross(b - a, c - a);
}

bool cmp(const Line& a, const Line& b) {
    ld A = get_angle(a), B = get_angle(b);
    //如果平行，那么就选靠左的一条
    if (!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0;
    return A < B;
}

//求出直线pv 和 qw 的交点坐标 注意这里用线段代替直线的方向，但是求出交点是直线的
//用p + v*t 点向式 来表示点
pdd get_line_intersection(pdd p, pdd v, pdd q, pdd w) {
    auto u = p - q;
    //此时将q视为坐标原点 向量平移过去
    ld t = cross(w, u) / cross(v, w);
    return {p.x + v.x * t, p.y + v.y * t};
}

//重载函数 求出两直线的交点
pdd get_line_intersection(Line &a, Line &b) {
    return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}

//叉积判断 直线b和c的交点是否在直线a的右侧
bool on_right(Line &a, Line &b, Line &c) {
    auto o = get_line_intersection(b, c);
    return sign(area(a.st, a.ed, o)) < 0; //<0 就保留点在直线上，<=就不保留
}

//半平面交
void half_plane_intersection() {
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

    int k = 0;
    for (int i = hh; i <= tt; i++)
        for (auto id : line[q[i]].ids)
            ans[k++] = id;
    sort(ans, ans + k);

    printf("%d\n", k);
    for (int i = 0; i < k - 1; i++) printf("%d ", ans[i]);
    printf("%d\n", ans[k - 1]);
}

int main() {
    map<pii, vector<int> > ids;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &ki[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &vi[i]);
    for (int i = 1; i <= n; i++)
        ids[ {ki[i], vi[i]}].push_back(i);

    line[cnt++] = {{0, 10000}, {0, 0}}; //y轴 向量方向向下 保证在左边半平面交
    line[cnt++] = {{0, 0}, {10000, 0}}; //x轴 向右

    //用y轴截距的点和 时间=1的直线的点 来表示直线
    for (auto &[k, v] : ids)
        line[cnt++] = {{0, k.x}, {1, k.x + k.y}, v};

    half_plane_intersection();

    return 0;
}
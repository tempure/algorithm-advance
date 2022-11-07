/*逆时针给出 n 个凸多边形的顶点坐标，求它们交的面积*/
#define x first
#define y second
typedef pair<double, double> pdd;
const int N = 510;
const double eps = 1e-8;
int cnt; //所有边的数量
struct Line {
    pdd st, ed; //用边的起点和终点表示有向边 起点指向终点
} line[N];
pdd pg[N], intersec[N]; //pg保存所有的边 intersec保存半平面交的轮廓点
int q[N]; //双端 单调队列
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
double get_angle(const Line &a) {  //得到一条直线的极角反正切值
    //反三角函数也是单调递增的 所以可以用来排序
    return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x);
}
pdd operator-(pdd a, pdd b) {
    return {a.x - b.x, a.y - b.y};
}
double cross(pdd a, pdd b) {
    return a.x * b.y - a.y * b.x;
}
double area(pdd a, pdd b, pdd c) {
    return cross(b - a, c - a);
}
bool cmp(const Line& a, const Line& b) {
    double A = get_angle(a), B = get_angle(b);
    //如果平行，那么就选靠左的一条
    if (!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0;
    return A < B;
}
//求出直线pv 和 qw 的交点坐标 注意这里用线段代替直线的方向，但是求出交点是直线的
//用p + v*t 点向式 来表示点
pdd get_line_intersection(pdd p, pdd v, pdd q, pdd w) {
    auto u = p - q;
    //此时将q视为坐标原点 向量平移过去
    double t = cross(w, u) / cross(v, w);
    return {p.x + v.x * t, p.y + v.y * t};
}
//重载函数 求出两直线的交点
pdd get_line_intersection(Line &a, Line &b) {
    return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}
//叉积判断 直线b和c的交点是否在直线a的右侧
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
int main() {
    int n, m;
    scanf("%d", &n);
    while (n --) {
        scanf("%d", &m);
        for (int i = 0; i < m; i++) scanf("%lf%lf", &pg[i].x, &pg[i].y);
        for (int i = 0; i < m; i++)
            line[cnt++] = {pg[i], pg[(i + 1) % m]}; //取模操作保证终点到起点的连边
    }
    double res = half_plane_intersection();
    printf("%.3lf\n", res);
    return 0;
}
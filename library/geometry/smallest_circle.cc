#define x first
#define y second
/*三点确定一个圆，每次枚举当一个点在当前最小圆外时候，此点必在新的最小圆的边上
用random_shuffle使点随机，复杂度均摊O(N)*/
typedef pair<double, double> pdd;
const int N = 100010;
const double eps = 1e-12;
const double PI = acos(-1);
int n;
pdd q[N];
struct Circle {
    pdd p; //圆心
    double r; //半径
};
int sign(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return -1;
}
int dcmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}
pdd operator- (pdd a, pdd b) {
    return {a.x - b.x,  a.y - b.y};
}
pdd operator+ (pdd a, pdd b) {
    return {a.x + b.x, a.y + b.y};
}
pdd operator* (pdd a, double t) {  //向量数乘
    return {a.x * t, a.y * t};
}
pdd operator/ (pdd a, double t) { //除一个常数
    return {a.x / t, a.y / t};
}
double operator* (pdd a, pdd b) { //叉积
    return a.x * b.y - a.y * b.x;
}
pdd rotate(pdd a, double b) {
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}
double get_dist(pdd a, pdd b) { //欧氏距离
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
pdd get_line_intersection(pdd p, pdd v, pdd q, pdd w) { //pv qw直线交点
    auto u = p - q;
    double t = w * u / (v * w); //叉乘
    return p + v * t;
}
pair<pdd, pdd> get_mid_line(pdd a, pdd b) { //求直线ab的中垂线
    return {(a + b) / 2, rotate(b - a, PI / 2)}; //起点是中点，方向是顺时针旋转90
}
Circle get_circle(pdd a, pdd b, pdd c) { //返回三点确定的圆
    auto u = get_mid_line(a, b), v = get_mid_line(a, c);
    auto p = get_line_intersection(u.x, u.y, v.x, v.y); //圆心
    return {p, get_dist(p, a)};
}
int main() {
    scanf("%d", &n); //n个点坐标
    for (int i = 0; i < n; i++) scanf("%lf%lf", &q[i].x, &q[i].y);
    random_shuffle(q, q + n);
    Circle c({q[0], 0}); //随便选一个点为初始圆 半径0
    for (int i = 1; i < n; i++) //从第二个点开始循环
        //如果点在圆外 就让该点为新圆边上的一个点 然后再找第三个点
        if (dcmp(c.r, get_dist(c.p, q[i])) < 0) {
            c = {q[i], 0};
            for (int j = 0; j < i; j++)
                if (dcmp(c.r, get_dist(c.p, q[j])) < 0) {
                    //新圆就是i，j为直径端点的圆
                    c = {(q[i] + q[j]) / 2, get_dist(q[i], q[j]) / 2};
                    for (int k = 0; k < j; k++)
                        if (dcmp(c.r, get_dist(c.p, q[k])) < 0)
                            c = get_circle(q[i], q[j], q[k]);
                }
        }
    printf("%.10lf\n", c.r); //半径
    printf("%.10lf %.10lf\n", c.p.x, c.p.y); //圆心坐标
    return 0;
}
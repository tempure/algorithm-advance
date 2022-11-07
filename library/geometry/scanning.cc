//求n个两条边分别与x轴和y轴平行的矩形的面积并,1<=n<=1000
#define x first
#define y second
/*横向区间排序 排序后处理每一个区间,对于每个区间，纵向排序+区间合并
复杂度O(N^2*logN),如果达到1e5，就需要扫描线+线段树处理了*/
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1010;
int n;
pii l[N], r[N]; //左上和右下坐标
pii q[N];
ll range_area(int a, int b) {
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (l[i].x <= a && r[i].x >= b) //该矩形横跨该区间
            q[cnt++] = {l[i].y, r[i].y};
    if (!cnt) return 0;
    sort(q, q + cnt); //纵向排序 + 区间合并
    ll res = 0;
    int st = q[0].x, ed = q[0].y;
    //区间合并
    for (int i = 1; i < cnt; i++)
        if (q[i].x <= ed) ed = max(ed, q[i].y);
        else {
            res += ed - st;
            st = q[i].x, ed = q[i].y;
        }
    res += ed - st; //最后一个区间
    return res * (b - a);
}
int main() {
    scanf("%d", &n);
    vector<int> xs; //所有的横坐标
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &l[i].x, &l[i].y, &r[i].x, &r[i].y);
        xs.push_back(l[i].x), xs.push_back(r[i].x);
    }
    sort(xs.begin(), xs.end());
    ll res = 0;
    for (int i = 0; i + 1 < xs.size(); i++) //枚举所有横向区间
        if (xs[i] != xs[i + 1])
            res += range_area(xs[i], xs[i + 1]);
    printf("%lld\n", res);
    return 0;
}
//求n个三角形面积并,1<=n<=100
#define x  first
#define y second
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
        //只处理横跨当前区间的 区间内的不要
        if (dcmp(t[0].x, a) > 0 || dcmp(t[2].x, a) < 0) continue;
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
                    auto o = get_line_intersection(tr[i][x], tr[i][(x + 1) % 3] - tr[i][x], tr[j][y], tr[j][(y + 1) % 3] - tr[j][y]);
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
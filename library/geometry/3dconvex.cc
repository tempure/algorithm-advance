const int N = 210; //多面体欧拉定理 面为2*边数-4
const double eps = 1e-12;
int n, m;
bool g[N][N]; //每条边相邻的2个面能否被照到
double rand_eps() { //随机扰动的幅度
    return ((double)rand() / RAND_MAX - 0.5) * eps;
}
struct Point {
    double x, y, z; //坐标
    void shake() { //随机扰动 防止四点共面
        x += rand_eps(), y += rand_eps(), z += rand_eps();
    }
    Point operator- (Point t) {
        return {x - t.x, y - t.y, z - t.z};
    }
    double operator& (Point t) { //内积
        return x * t.x + y * t.y + z * t.z;
    }
    Point operator* (Point t) { //外积返回向量 用行列式计算
        return {y * t.z - t.y * z, z * t.x - x * t.z, x * t.y - y * t.x};
    }
    double len() { //向量模长
        return sqrt(x * x + y * y + z * z);
    }
} q[N];
struct Plane {
    int v[3]; //三点确定的三角形面
    Point norm() { //返回平面法向量 外积即可
        return (q[v[1]] - q[v[0]]) *  (q[v[2]] - q[v[0]]);
    }
    double area() { //三角形面积
        return norm().len() / 2;
    }
    bool above(Point a) { //判断点a在该平面上还是下 上是指凸包向外的方向
        //和法向量在同一侧 cosθ>=0
        return ((a - q[v[0]]) & norm()) >= 0;
    }
} plane[N], np[N]; //np是备份数组
void get_convex_3d() {
    plane[m++] = {0, 1, 2};
    plane[m++] = {2, 1, 0}; //用点的逆时针编号来存面 初始化存一个正反面
    for (int i = 3; i < n; i++) { //枚举增量加入所有的点
        //每次更新凸包中的面是不能被照到的面+分解轮廓和新的点构成的所有面
        int cnt = 0;
        for (int j = 0; j < m; j++) { //增删所有已经加入的面
            bool t = plane[j].above(q[i]);
            if (!t) np[cnt++] = plane[j]; //不能照到就保留下来
            for (int k = 0; k < 3; k++)
                //维护该面的三条边 更新该边左边的面能否被照到
                g[plane[j].v[k]][plane[j].v[(k + 1) % 3]] = t;
        }
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 3; k++) {
                int a = plane[j].v[k], b = plane[j].v[(k + 1) % 3];
                //该边只有一个相邻的面能被照到，那么该边就是目前的一个边界轮廓
                //然后轮廓线向新加入的点构成的平面加入凸包中
                if (g[a][b] && !g[b][a]) np[cnt++] = {a, b, i};
            }
        m = cnt;
        for (int j = 0; j < m; j++) plane[j] = np[j]; //复制回palne[]
    }
}
int main() {
    scanf("%d", &n); //顶点个数
    for (int i = 0; i < n; i++) {//顶点坐标
        scanf("%lf%lf%lf", &q[i].x, &q[i].y, &q[i].z);
        q[i].shake();
    }
    get_convex_3d();
    double res = 0;
    for (int i = 0; i < m; i++) //m是面数量
        res += plane[i].area();
    printf("%lf\n", res); //凸包面积
    return 0;
}
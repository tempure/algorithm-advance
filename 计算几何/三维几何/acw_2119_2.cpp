/*
增量算法，O(N^2)
点照到的分界线划分技巧：每个三角形的面都使用逆时针存储，由于面和面都是相接的
定义每个平面朝向球外的法向量方向为正，开一个bool数组，标记当前增量加入的新点是在平面的上面还是下面
这里的上下指的是和法向量的夹角。
如果一个边相接的两个面，新的点在一个面的上面，在另外一个面的下面，那么bool数组标记即可，此边就是当前一轮的分界线之一

防止出现四点共面，采用微扰，此时就不能使用 sign 或者 dcmp 这种 eps 近似函数来判断正负或者想等了
因为近似计算会忽略掉微扰操作的效果
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 210; //plane = 2 * point - 4, edge = 3 * point - 6
const double eps = 1e-12;

int n, m;
bool  g[N][N];

double rand_eps() {
    return ((double)rand() / RAND_MAX - 0.5) * eps; //[-0.5,0.5] * eps
}

struct Point {
    double x, y, z;
    void shake() {
        x += rand_eps(), y += rand_eps(), z += rand_eps();
    }
    Point operator-(Point t) {
        return {x - t.x, y - t.y, z - t.z};
    }
    double operator&(Point t) {
        return x * t.x + y * t.y + z * t.z;
    }
    Point operator*(Point t) {
        return {y * t.z - t.y * z, z * t.x - x * t.z, x * t.y - y * t.x};
    }
    double len() {
        return sqrt(x * x + y * y + z * z);
    }
} q[N];

struct Plane {
    int v[3];
    Point norm() {
        return (q[v[1]] - q[v[0]]) * (q[v[2]] - q[v[0]]);
    }
    double area() {
        return norm().len() / 2;
    }
    bool above(Point a) {
        return ((a - q[v[0]]) & norm()) >= 0;
    }
} plane[N], np[N];

void get_convex_3d() {
    plane[m++] = {0, 1, 2};
    plane[m++] = {2, 1, 0}; //用点的逆时针编号来存面 初始化存一个正反面 {0,2,1}也可以

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

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> q[i].x >> q[i].y >> q[i].z;
        q[i].shake();
    }
    get_convex_3d();
    double res = 0;
    for (int i = 0; i < m;  i++ )
        res += plane[i].area();
    printf("%lf\n", res);
}

int main() {
    solve();
    return 0;
}
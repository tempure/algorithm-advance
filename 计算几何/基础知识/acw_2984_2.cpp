#include<bits/stdc++.h>
using namespace std;
using pdd = pair<double, double>;
const int N = 210;
const double eps = 1e-8;
#define x first
#define y second

int n;
pdd q[N], a[N], b[N]; //q[] all points, a[] one side of seg, b[] anoter side poin of every seg

int sign(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

int cmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    else return 1;
}

double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}

double area(pdd a, pdd b, pdd c) {
    return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

bool check() {
    for (int i = 0; i < 2 * n; i++)
        for (int j = i + 1; j < 2 * n; j++) {
            //i,j为相同的点，不能勾成线段 特判，也就是两个线段有一个端点重合
            if (!cmp(q[i].x, q[j].x) && !cmp(q[i].y, q[j].y)) continue;
            bool flag = true;
            for (int k = 0; k < n; k++)
                //务必使用直线来作为跨立的分界线，因为cross函数本质是用向量来计算
                //如果用线段作为分界，当线段完全在直线一侧时，会误判为正确
                if (sign(area(q[i], q[j], a[k])) * sign(area(q[i], q[j], b[k])) > 0) {
                    flag = false;
                    break;
                }
            if (flag) return true;
        }
    return false;
}

void solve() {
    cin >> n;
    for (int i = 0, k = 0; i < n; i++) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        q[k++] = {x1, y1}, q[k++] = {x2, y2};
        a[i] = {x1, y1}, b[i] = {x2, y2};
    }
    if (check()) puts("Yes!");
    else puts("No!");
}

int main() {
    int t;
    cin >> t;
    while (t --) solve();
    return 0;
}
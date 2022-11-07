#include <bits/stdc++.h>
using namespace std;
using pdd = pair<double, double>;
#define x first
#define y second

//较好的题解：https://www.acwing.com/solution/content/26937/

const int N  = 210;
const double eps = 1e-8;
int n;
pdd q[N], a[N], b[N];

int sign(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    else return 1;
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
            if (!cmp(q[i].x, q[j].x) && !cmp(q[i].y, q[j].y)) continue;
            bool flag = true;
            //q[i]--q[j] is a line,  k enuerate all segments
            for (int k = 0; k < n; k++) {
                if (sign(area(q[i], q[j], a[k])) * sign(area(q[i], q[j], b[k])) > 0) {
                    flag = false;
                    break;
                }
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
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
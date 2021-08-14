#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
using pdd = pair<double, double>;

const int N = 40010;
const double pi = acos(-1);

int n, cnt;
pdd q[N];
int stk[N], top;
bool used[N];

pdd operator-(pdd a, pdd b) {
    return {a.x - b.x, a.y - b.y};
}

pdd rotate(pdd a, double b) {
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}

double cross(pdd a, pdd b) {
    return a.x * b.y - a.y * b.x;
}

double area(pdd a, pdd b, pdd c) {
    return cross(b - a, c - a);
}

double get_dist(pdd a, pdd b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}


double andrew() {
    sort(q, q + cnt);
    int top = 0;
    for (int i = 0; i < cnt; i++) { //下凸壳
        while (top >= 2 && area(q[stk[top - 1]], q[stk[top]], q[i]) <= 0) {
            // 凸包边界上的点即使被从栈中删掉，也不能删掉used上的标记
            if (area(q[stk[top - 1]], q[stk[top]], q[i]) < 0)
                used[stk[top--]] = false;
            else top --;
        }
        stk[++top] = i; //栈顶下标从1开始
        used[i] = true;
    }

    //将起点再一次入栈
    used[0] = false;
    for (int i = cnt - 1; i >= 0; i--) { //求上凸壳
        if (used[i]) continue;
        while (top >= 2 && area(q[stk[top - 1]], q[stk[top]], q[i]) <= 0)
            top -- ;
        stk[ ++ top] = i;
    }

    double res = 0; //起点入栈2次 一个在栈底 一个在栈顶
    for (int i = 2; i <= top; i++)
        res += get_dist(q[stk[i - 1]], q[stk[i]]);
    return res;
}

void solve() {
    cin >> n;
    double a, b, r;
    cin >> a >> b >> r;
    a = a / 2 - r, b = b / 2 - r;
    int dx[] = {1, 1, -1, -1}, dy[] = {1, -1, -1, 1};
    while (n --) {
        double x, y, z;
        scanf("%lf%lf%lf", &x, &y, &z);
        for (int i = 0; i < 4; i++) {
            //先在原点旋转四个角上的圆心 然后平移到自己的位置
            auto t = rotate({dx[i] * b, dy[i] * a}, -z); //顺时针旋转z就是逆时针旋转-z
            q[cnt++] = {x + t.x, y + t.y};
        }
    }
    double res = andrew();
    printf("%.2lf\n", res + 2 * pi * r);  //加上圆周长
}

int main() {
    solve();
    return 0;
}
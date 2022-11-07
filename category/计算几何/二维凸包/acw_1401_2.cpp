#include  <bits/stdc++.h>
using namespace  std;
#define x first
#define y second
using pdd = pair<double, double>;

const int N = 1e5 + 10;
int n;
pdd q[N];
int stk[N];
bool used[N];

double get_dist(pdd a, pdd b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
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

double andrew() {
    sort(q, q + n);
    int top = 0;
    for (int i = 0; i < n; i++) {
        /*
        凸包边缘上共线的点不嫩删除used标记，考虑所有点都在一条直线上
        如果第一遍求凸包的时候把中间共线的点used都删掉了
        那么反过来求第二次的时候，会重复入栈，导致多算，本题求的是距离
        */
        while (top >= 2 && area(q[stk[top - 1]], q[stk[top]], q[i]) <= 0) {
            if (area(q[stk[top - 1]], q[stk[top]], q[i]) < 0)
                used[stk[top--]] = false;
            else top--;
        }
        stk[++top] = i;
        used[i] = true;
    }
    used[0] = false;
    for (int i = n - 1; i >= 0; i--) {
        if (used[i]) continue;
        //反过来求的时候就不用再把用过的点打上 used 标记了，因为不会再用到回去的那些点了
        while (top >= 2 && area(q[stk[top - 1]], q[stk[top]], q[i]) <= 0)
            top --;
        stk[++top] = i;
    }

    double res = 0;
    for (int i = 2; i <= top; i++)
        res += get_dist(q[stk[i - 1]], q[stk[i]]);
    return res;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> q[i].x >> q[i].y;
    double res = andrew();
    printf("%.2lf\n", res);
}

int main() {
    solve();
    return 0;
}
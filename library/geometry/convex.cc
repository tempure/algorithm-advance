#define x first
#define y second
typedef pair<double, double> pdd;
const int N = 10010;
int n;
pdd q[N];  //所有的点
int stk[N]; //栈
bool used[N]; //标记是否被用过
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
double area(pdd a, pdd b, pdd c) { //ab 和 ac向量的叉积
    return cross(b - a, c - a);
}
double andrew() {
    sort(q, q + n);
    int top = 0;
    for (int i = 0; i < n; i++) { //下凸壳
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
    for (int i = n - 1; i >= 0; i--) { //求上凸壳
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
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf%lf", &q[i].x, &q[i].y);
    double res = andrew();
    printf("%.2lf\n", res);
    return 0;
}
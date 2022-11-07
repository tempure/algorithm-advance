//整数二分
bool check(int x) {/* ... */} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid]和[mid + 1, r]时使用：
int bsearch_1(int l, int r) {
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}
// 区间[l, r]被划分成[l, mid - 1]和[mid, r]时使用：
int bsearch_2(int l, int r) {
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}
/*
    例题:给定一个按照升序排列的长度为n的整数数组，q个查询。
    对于每个查询，返回一个元素k的起始位置和终止位置(位置从0开始计数)
    如果数组中不存在该元素，则返回“-1 -1”。
*/
const int N = 100010;
int a[N];
int main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    while (q--) {
        int x; cin >> x;
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (a[mid] >= x) r = mid; //注意此处相等也要继续
            else l = mid + 1;
        }
        if (a[l] != x) cout << "-1 -1" << endl;
        else {
            cout << l << ' ';
            l = 0, r = n - 1;
            while (l < r) {
                int mid = l + r + 1 >> 1;
                if (a[mid] <= x) l = mid;
                else r = mid - 1;
            }
            cout << r << endl;
        }
    }
    return 0;
}
//浮点数二分
double bsearch_3(double l, double r) {
    const double eps = 1e-6;
    // eps 表示精度，取决于题目对精度的要求
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    return l;
}
//例题：给定一个浮点数n，求它的三次方根，结果保留6位小数。
//数据范围−10000 <= n <= 10000
int main() {
    double x; scanf("%lf", &x);
    double l = -10000; double r = 10000;
    double eps = 1e-8; //精度一般取比题目 要求多2位即可
    while (r - l > eps) {
        double mid = (r + l) / 2;
        if (mid * mid * mid <= x) l = mid;
        else r = mid;
    }
    printf("%f", l);
}
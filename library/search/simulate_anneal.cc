/*POJ2420在二维平面上有 n 个点，第 i 个点的坐标为 (xi,yi)
找出一个点使得该点到这 n 个点的距离之和最小。输出最小距离和,四舍五入取整。O(N*logT),T为坐标范围的3倍
需要函数连续才可以,初始温度为坐标的最值，终止温度设为同样数量级的小数即可。这题比较直观，就是距离，所以可以直接用温度来控制每次随机点的区域步长。
这里就是用当前点所在的矩形区域内随机一个点。随机之后的点比当前点更优，就直接跳过去，如果不优，就根据不优的程度选择概率跳过去。
求最小值还是最大值，只需要改exp> or < rand(0,1)这一行代码即可
关于迭代次数:通常可以试100/1000次，大数据可以用卡评测时间来决定迭代的次数。如果TLE,除了迭代次数之外，那就需要调整衰减系数，调小一些，衰减更快。此题本质上是单峰函数，所以0.9的衰减系数就可以搜到，但是0.999就会超时*/
#define x first
#define y second
typedef pair<double, double> pdd;
const int N = 110;
int n;
pdd q[N]; //所有点坐标
double ans = 0x3f3f3f3f; //答案 最小值
double rand(double l, double r) { //返回[l,r)内的一个随机数
    return (double)rand() / RAND_MAX * (r - l) + l;
}
double get_dist(pdd a, pdd b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
double calc(pdd p) { //当前点距离求和
    double res = 0;
    for (int i = 0; i < n; i++)
        res += get_dist(p, q[i]);
    ans = min(ans, res);
    return res;
}
void simulate_anneal() {
    pdd cur(rand(0, 10000), rand(0, 10000));
    //初始温度 结束温度  衰减系数
    for (double t = 1e4; t > 1e-4; t *= 0.9) {
        //当前点为中心当前温度作为步长的正方形区域随机选一点
        pdd np(rand(cur.x - t, cur.x + t), rand(cur.y - t, cur.y + t));
        double dt = calc(np) - calc(cur);
        if (exp(-dt / t) > rand(0, 1)) cur = np;
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf%lf", &q[i].x, &q[i].y);
    //做100次模拟退火 这是估计的迭代次数
    //大数据可以用卡时的方法,比如卡0.8s
    //while ((double)clock() / CLOCKS_PER_SEC < 0.8) smimulate_anneal();
    for (int i = 0; i < 100; i++) simulate_anneal();
    printf("%0.lf\n", ans);
    return 0;
}
/*HAOI2006《均分数据》给出N个正整数A1、A2...An分成M组使得各组数据的数值和最平均即各组的均方差最小。输出最小均方差(保留小数点后两位)*/
/*每次随机一个序列贪心,每次都将当前要放的数放在和最小的组中*/
const int N = 25, M = 10;
int n, m;
int w[N], s[M];
double ans = 1e8;
double calc() {
    memset(s, 0, sizeof s);
    for (int i = 0; i < n; i++) {
        int k = 0;
        for (int j = 0; j < m; j++)
            if (s[j] < s[k]) //找出和最小的组
                k = j;
        s[k] += w[i];
    }
    double avg = 0;
    for (int i = 0; i < m; i++) avg += (double)s[i] / m;
    double res = 0;
    for (int i = 0; i < m; i++)
        res += (s[i] - avg) * (s[i] - avg);
    res = sqrt(res / m);
    ans = min(ans, res);
    return res;
}
void simulate_anneal() {
    random_shuffle(w, w + n);
    for (double t = 1e6; t > 1e-6; t *= 0.95) {
        //交换序列中的2个数
        int a = rand() % n, b = rand() % n;
        double x = calc();
        swap(w[a], w[b]);
        double y = calc();
        double delta = y - x;
        if (exp(-delta / t) < (double)rand() / RAND_MAX)
            swap(w[a], w[b]);
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < 100; i++) simulate_anneal();
    printf("%.2lf\n", ans);
    return 0;
}
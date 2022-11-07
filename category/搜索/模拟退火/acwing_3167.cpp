#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

/*
模拟退火模板题：

前提:模拟退火需要函数连续才可以

初始温度为坐标的最值，终止温度设为同样数量级的小数即可
这题比较直观，就是距离，所以可以直接用温度来控制每次随机点的区域步长
这里就是用当前点所在的矩形区域内随机一个点
随机之后的点比当前点更优，就直接跳过去，如果不优，就根据不优的程度选择概率跳过去
求最小值还是最大值，只需要改exp> or < rand(0,1)这一行代码即可

关于迭代次数:通常可以试100/1000次，大数据可以用卡评测时间来决定迭代的次数
如果TLE,除了迭代次数之外，那就需要调整衰减系数，调小一些，衰减更快

此题本质上是单峰函数，所以0.9的衰减系数就可以搜到，但是0.999就会超时
*/

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
    for (double t = 1e4; t > 1e-4; t *= 0.9) { //初始温度 结束温度  衰减系数
        //当前点为中心，长度为当前温度作为步长的正方形区域内随机选一个点
        pdd np(rand(cur.x - t, cur.x + t), rand(cur.y - t, cur.y + t));
        double dt = calc(np) - calc(cur);
        if (exp(-dt / t) > rand(0, 1)) cur = np;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf%lf", &q[i].x, &q[i].y);

    //做100次模拟退火 这是估计的，大数据可以用卡时的方法
    for (int i = 0; i < 100; i++) simulate_anneal();
    printf("%0.lf\n", ans);

    return 0;
}
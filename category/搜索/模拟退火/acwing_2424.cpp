#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

/*
每次随机交换2个位置即可，用卡时来控制时间
*/

typedef pair<int, int> pii;
const int N = 55;

int n, m;
pii q[N];
int ans;

int calc() {
    int res = 0;
    for (int i = 0; i < m; i++) {
        res += q[i].x + q[i].y;
        if (i < n) {
            if (q[i].x == 10) res += q[i + 1].x + q[i + 1].y;
            else if (q[i].x + q[i].y == 10)
                res += q[i + 1].x;
        }
    }
    ans = max(res, ans);
    return res;
}

void smimulate_anneal() {
    for (double t = 1e4; t > 1e-4; t *= 0.99) {
        int a = rand() % m, b = rand() % m;  //随机交换2个顺序
        int x = calc(); //交换前的得分
        swap(q[a], q[b]);
        if (n + (q[n - 1].x == 10) == m) { //保证第N轮10分的不会被破坏
            int y = calc(); //交换后的结果
            int delta = y - x;
            //这里求的是最大值，如果变小了，就换回来
            if (exp(delta / t) < (double)rand() / RAND_MAX)
                swap(q[a], q[b]);
        }
        else swap(q[a], q[b]); //此交换破坏了N+1轮 就换回来
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &q[i].x, &q[i].y);
    if (q[n - 1].x == 10) m = n + 1, scanf("%d%d", &q[n].x, &q[n].y);
    else m = n;

    //卡0.8s，如果用次数迭代，要根据函数有多少个局部最优解来确定迭代次数
    while ((double)clock() / CLOCKS_PER_SEC < 0.8) smimulate_anneal();

    printf("%d\n", ans);

    return 0;
}
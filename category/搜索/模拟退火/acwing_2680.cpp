#include <bits/stdc++.h>
using namespace std;

/*
每次随机一个序列，然后贪心
每次都将当前要放的数，放在和最小的组中
*/

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
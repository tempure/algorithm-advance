#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef pair<double, double> pdd;
const int N = 55, M = N * N; //M是点数上界

int n, m, k;
int l[M], r[M], u[M], d[M], row[M], col[M], s[M], idx;
bool st[N];
pdd city[N], station[N]; //城市和雷达站

/*
二分+DLX重复覆盖
二分半径，求出当前半径选多少个雷达站即可覆盖所有城市，如果当前半径下求出的雷达站数量>=k
那就减小半径，直到二分最后的答案即可。

每次二分，用雷达站作为DLX的行，城市作为列，枚举每个雷达站，如果和城市的距离<=当前半径，那就连边即可。
*/

void init() {
    for (int i = 0; i <= n; i++) {
        l[i] = i - 1, r[i] = i + 1;
        col[i] = u[i] = d[i] = i;
        s[i] = 0;
    }
    l[0] = n, r[n] = 0;
    idx = n + 1;
}

void add(int &hh, int &tt, int x, int y) {
    row[idx] = x, col[idx] = y, s[y] ++;
    u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx ++;
}

int h() {
    int res = 0;
    memset(st, 0, sizeof st);
    for (int i = r[0]; i; i = r[i]) {
        if (st[i]) continue;
        res ++;
        st[i] = true;
        for (int j = d[i]; j != i; j = d[j])
            for (int k = r[j]; k != j; k = r[k])
                st[col[k]] = true;
    }
    return res;
}

void remove(int p) {
    for (int i = d[p]; i != p; i = d[i]) {
        r[l[i]] = r[i];
        l[r[i]] = l[i];
    }
}

void resume(int p) {
    for (int i = u[p]; i != p; i = u[i]) {
        r[l[i]] = i;
        l[r[i]] = i;
    }
}

bool dfs(int k, int depth) {
    if (k + h() > depth) return false;
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[p] > s[i])
            p = i;
    for (int i = d[p]; i != p; i = d[i]) {
        remove(i);
        for (int j = r[i]; j != i; j = r[j]) remove(j);
        if (dfs(k + 1, depth)) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(j);
        resume(i);
    }
    return false;
}

bool check(pdd a, pdd b, double mid) { //城市和雷达站距离是否小于等于mid
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy <= mid * mid;
}

bool check(double mid) { //二分当前dlx
    init(); //每次二分都要初始化
    for (int i = 1; i <= m; i++) {
        int hh = idx, tt = idx;
        for (int j = 1; j <= n; j++)
            if (check(station[i], city[j], mid))
                add(hh, tt, i, j);
    }

    int depth = 0;
    while (depth <= k && !dfs(0, depth)) depth++;
    return depth <= k;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++) scanf("%lf%lf", &city[i].x, &city[i].y);
        for (int i = 1; i <= m; i++) scanf("%lf%lf", &station[i].x, &station[i].y);
        double l = 0, r = 1600; //r是最大的距离为1000*sqrt(2)
        while (r - l > 1e-10) {
            double mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid;
        }
        printf("%lf\n", r);
    }
    return 0;
}
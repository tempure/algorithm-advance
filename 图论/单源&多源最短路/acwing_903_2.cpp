#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//建立一个虚拟原点
//虚拟原点到每个点的边的权值 就是直接买的价格
//除了虚拟原点之外的点之间存在可以优惠的关系
//每次只更新 等价差距内的点 然后最后再所有等级的区间都取min

const int N = 110;
const int INF = 0x3f3f3f3f;
int n, m;
int w[N][N], level[N];
int dist[N];
bool st[N];

int dijkstra(int down, int up) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);

    dist[0] = 0;
    for (int i = 1; i <= n + 1; i ++) {
        int t = -1;
        for (int j = 0; j <= n; j++) //0虚拟原点要对其邻点进行更新
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;

        st[t] = true;
        for (int j = 1; j <= n; j ++) //如果在区间范围内就更新区间
            if (level[j] >= down && level[j] <= up)
                dist[j] = min(dist[j], dist[t] + w[t][j]);
    }

    return dist[1];
}

int main() {
    cin >> m >> n;
    // memset(dist, 0x3f, sizeof dist);
    memset(w, 0x3f, sizeof w);
    for (int i = 1; i <= n; i++) w[i][i] = 0;
    //虚拟原点定位为0号点
    for (int i = 1; i <= n; i++) {
        int price, cnt;
        cin >> price >> level[i] >> cnt;
        w[0][i] = min(price, w[0][i]);
        while (cnt --) {
            int id, cost;
            cin >> id >> cost;
            w[id][i] = min(cost, w[id][i]);
        }
    }

    int res  = INF;
    //枚举等级区间范围 和酋长超过m范围的点 就不能交易了
    //0号虚拟远点的level是0，而所有题目中的点level都是>=1所以虚拟源点不会在区间遍历中被更新
    //因为只有和酋长level差m以内的才能和酋长交易，所以直接暴力枚举这个等级区间即可
    for (int i = level[1] - m; i <= level[1]; i++) res = min(res, dijkstra(i, i + m));

    cout << res << endl;
    return 0;
}
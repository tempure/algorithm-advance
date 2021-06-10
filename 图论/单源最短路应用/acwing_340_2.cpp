#include <iostream>
#include <cstring>
#include <deque>
using namespace std;

const int N = 1010, M = 20010;
int h[N], e[M], ne[M], idx, w[M];
int d[N];
bool v[N];
int n, m, k;

/*
单源最短路+二分
注意题意只需要考虑一条通路即可，不是支付其余的所有路径
也就是让路径的第k + 1 大数最小 二分x即可: 比x大的数个数是否<= k 满足则减小x
将所有边分类：比x大边权为1 比x小则边权为0，然后双端队列BFS求最短路
也可以用分层图 拆点来做

双端队列BFS: 能求出图中只有0、1两种边权的图的最短路，线性复杂度
相对于普通BFS唯一的区别就是，当前点的邻边如果边权为0，那么加入对头，否则加入队尾

所有BFS问题的证明可以转化为dijkstra算法的证明，由于dijkstra算法正确，原问题正确
dijkstra严格来说可以求出所有边都是非负的，即使边权是0也可以

0加入对头，1加入队尾，队列中的元素同时满足单调性，类比dijkstra算法队列中的单调性即可
*/

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool check(int bound) {
    memset(d, 0x3f, sizeof d);
    memset(v, 0, sizeof v);
    deque<int> q;
    d[1] = 0;
    q.push_back(1);

    while (q.size()) {
        auto t = q.front(); q.pop_front();
        if (v[t]) continue;
        v[t] = 1;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i], v = w[i] > bound;
            if (d[j] > d[t] + v) {
                d[j] = d[t] + v;
                if (!v) q.push_front(j);
                else q.push_back(j);
            }
        }
    }
    return d[n] <= k;
}

int main() {
    cin >> n >> m >> k;
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b , c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    int l = 0, r = 1e6 + 1; //如果图不连通 最短路返回INF 最终会r为右边界，注意有边界要大于所有题目数据范围
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    if (r == 1e6 + 1) puts("-1");
    else cout << r << endl;

    return 0;
}
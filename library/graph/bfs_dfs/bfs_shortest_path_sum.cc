/*
给出一个 N 个顶点 M 条边的无向无权图，顶点编号为 1 到 N。
问从顶点 1 开始，到其他每个点的最短路有几条。
输入格式
第一行包含 2 个正整数 N,M，为图的顶点数与边数。
接下来 M 行，每行两个正整数 x,y，表示有一条顶点 x 连向顶点 y 的边，请注意可能有自环与重边。
输出格式
输出 N 行，每行一个非负整数，第 i 行输出从顶点 1 到顶点 i 有多少条不同的最短路，由于答案有可能会很大，你只需要输出对 100003 取模后的结果即可。
如果无法到达顶点 i 则输出 0。
*/
//先求出到每个点的最短路的值 然后分别求出有多少路径
//最短路树 也就是拓扑图 记录每个点的 前驱
//最短路的求解过程 需要满足拓扑序 只有dijkstra/bfs满足入队出队一次就是最优 拓扑序的遍历
//spfa实际上也可以，如果有负权的话

const int N = 100010, M = 400010;
const int mod = 100003;
int n, m;
int h[N], e[M], ne[M], idx;
int dist[N], cnt[N];
int q[N];
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
void bfs() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    cnt[1] = 1; //原点到自己的初始最短路就是1
    int hh = 0, tt = 0;
    q[0] = 1;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + 1) { //更新最短路 同时更新 cnt
                dist[j] = dist[t] + 1;
                cnt[j] =  cnt[t]; //j第一次被t更新
                q[++tt] =  j;
            }
            //j已经被其他点更新过了，已经最优了，直接加上
            else if (dist[j] == dist[t] + 1) {
                cnt[j] = (cnt[j] + cnt[t]) % mod;
            }
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    bfs();
    for (int i = 1; i <= n; i++) printf("%d\n", cnt[i]);
    return 0;
}
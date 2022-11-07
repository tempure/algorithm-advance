/*
例题:第k短路
给定一张N个点（编号1,2…N），M条边的有向图，求从起点S到终点T的第K短路的长度，路径允许重复经过点或边。
输入格式:第一行包含两个整数N和M。
接下来M行，每行包含三个整数A,B和L，表示点A与点B之间存在有向边，且边长为L。
最后一行包含三个整数S,T和K分别表示起点S终点T和第K短路
输出格式
输出占一行，包含一个整数，表示第K短路的长度，如果第K短路不存在，则输出“-1”。
*/
#define x first
#define y second
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
/*
    将队列换成优先队列 小根堆
    A-star可以处理任意边权不论正负，但是不能有负权回路，不需要BFS强制的边权为1
    如果无解，那就不如朴素的BFS，因为A-star每一次都是堆操作，log，但是朴素BFS是线性
    A*算法只能保证终点出队是最小值，中间的点出队不一定是最优的
    但是dijkstra每个点出队 就已经是最优的了
    每个点不一定只被扩展一次 可能会被多次遍历 找最优解
*/
const int N = 1010, M = 200010; //要建反图，求出最短距离 就是估价函数
int n, m, S, T, K;
int h[N], rh[N], e[M], w[M], ne[M], idx;
int dist[N];
bool st[N];  //dijkstra 标记哪个点没有被用过
int cnt[N]; //每个点被搜过的次数
void add(int h[], int  a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void dijkstra() { //预处理估价函数dist数组
    //反向求一遍最短路 处理估价函数 注意 这里只处理该点到终点的最短路，
    //当前点到起点的距离 可能依然不是最优的
    priority_queue<pii, vector<pii>, greater<pii> > heap;
    //先把终点加进去
    heap.push({0, T});
    memset(dist, 0x3f, sizeof dist);
    dist[T] = 0;
    while (heap.size()) {
        auto t = heap.top();
        heap.pop();
        int ver = t.y;
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = rh[ver]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}
int astar() {
    priority_queue<piii, vector<piii>, greater<piii> > heap;
    heap.push({dist[S], {0, S}}); //起点的估价值真实值和点编号
    // int cnt = 0; //终点被遍历的次数
    while (heap.size()) {
        auto t = heap.top();
        heap.pop();
        int ver = t.y.y, distance = t.y.x; //distance真实距离 就是起点到该点的距离
        cnt[ver] ++;
        if (cnt[T] == K) return distance;
        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i]; //邻接的点j的估价值 加上
            if (cnt[j] < K) heap.push({distance + w[i] + dist[j], {distance + w[i], j}});
        }
    }
    return -1;
}
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    memset(rh, -1, sizeof rh);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(h, a, b, c); //正边
        add(rh, b, a, c); //反向边
    }
    scanf("%d%d%d", &S, &T, &K);
    if (S == T) K ++; //最短路至少有一条边 如果是环的情况，那就把0这种情况除掉
    dijkstra();
    printf("%d\n", astar());
    return 0;
}
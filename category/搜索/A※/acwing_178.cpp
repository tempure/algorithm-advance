/*
* @Description: 178. 第K短路
* @Author: Xiaobin Ren
* @Date:   2020-10-17 12:57:06
* @Last Modified time: 2020-10-17 12:57:25
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define x first
#define y second
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

/*  搜索空间非常大的时候，需要A star算法 优化 只需要搜索很小的一部分点
    将队列换成优先队列 小根堆
    A-star可以处理任意边权不论正负，但是不能有负权回路，不需要BFS强制的边权为1
    dijkstra是估价函数都取0的特殊的A-star算法
    如果无解，那就不如朴素的BFS，因为A-star每一次都是堆操作，log，但是朴素BFS是线性
    A-star算法只能保证终点出队是最小值，中间的点 出队 不一定是最优的
    但是dijkstra每个点出队 就已经是最优的了
    每个点不一定只被扩展一次 可能会被多次遍历 找最优解
*/

const int N = 1010, M = 200010; //要建反图，求出最短距离 就是估计函数
int n, m, S, T,K;
int h[N], rh[N],e[M], w[M], ne[M], idx;
int dist[N];
bool st[N];  //dijkstra 标记哪个点没有被用过
int cnt[N]; //每个点被搜过的次数

void add(int h[], int  a, int b, int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void dijkstra(){ //预处理估价函数dist数组
    //反向求一遍最短路 处理估价函数 注意 这里只处理该点到终点的最短路，
    //当前点到起点的距离 可能依然不是最优的
    priority_queue<pii, vector<pii>, greater<pii> > heap;
    //先把终点加进去
    heap.push({0, T});
    
    memset(dist, 0x3f, sizeof dist);
    
    dist[T] = 0;
    
    while(heap.size()){
        auto t = heap.top();
        heap.pop();
        
        int ver = t.y;
        if(st[ver]) continue;
        st[ver] = true;
        
        for(int i = rh[ver]; ~i; i = ne[i]){
            int j = e[i];
            if(dist[j] > dist[ver] + w[i]){
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}

int astar(){
    priority_queue<piii, vector<piii>, greater<piii> > heap;
    heap.push({dist[S], {0, S}}); //起点的估价值，真实值和点的编号
    
    // int cnt = 0; //终点被遍历的次数
    
    while(heap.size()){
        auto t = heap.top();
        heap.pop();
        
        int ver = t.y.y, distance = t.y.x; //distance真实距离 就是起点到该点的距离
        cnt[ver] ++;
        // if(ver == T) cnt[T] ++;
        if(cnt[T] == K) return distance;
        
        for(int i = h[ver]; ~i; i = ne[i]){
            int j =e[i]; //邻接的点j的估价值 加上
            if(cnt[j] < K) heap.push({distance + w[i] + dist[j], {distance + w[i], j}});
        }
    }
    
    return -1;
}

int main(){
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    memset(rh, -1, sizeof rh);
    
    for(int i = 0; i < m; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(h, a, b, c); //正边
        add(rh, b, a, c); //反向边
    }
    
    scanf("%d%d%d", &S, &T, &K);
    if(S == T) K ++; //最短路至少有一条边 如果是环的情况，那就把0这种情况除掉
    
    dijkstra();
    printf("%d\n", astar());
    
    return 0;
}
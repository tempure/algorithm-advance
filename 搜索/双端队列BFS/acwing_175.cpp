/*
* @Description: 175. 电路维修
* @Author: Xiaobin Ren
* @Date:   2020-10-16 18:07:20
* @Last Modified time: 2020-10-16 18:07:32
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>
#define x first
#define y second
using namespace std;
typedef pair<int, int> pii;

//一个点的横纵坐标和是奇数 就不能到达 偶数就可以到达
//这个图的边权只有0和1，能走就是1，不能走就是0
//将0插入队头，1插入队尾，这样才能保住队列的单调性

const int N = 510, M = N * N;
int n, m;
char g[N][N];
int dist[N][N];
bool st[N][N];  //判重

int bfs(){
    deque<pii> q;
    //每个点只会入队一次
    int hh = 0, tt = 0;
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    
    char cs[] = "\\/\\/";
    
    //每个点对角线可以走到的4个点
    int dx[4] = {-1, -1, 1, 1}, dy[4] = {-1, 1, 1, -1};
    //每个点 周围的4个斜线的坐标转换
    int ix[4] = {-1, -1, 0, 0}, iy[4] = {-1, 0, 0, -1};  
    
    dist[0][0] = 0;
    q.push_back({0, 0});
    
    while(q.size()){
        auto t = q.front();
        q.pop_front();
        
        int x = t.x, y = t.y;
        
        if(x == n && y == m) return dist[x][y];
        
        if(st[x][y]) continue;
        st[x][y] = true;
        
        for(int i = 0 ; i < 4; i++){
            int a = x + dx[i], b = y + dy[i];
            if(a < 0 || a >n || b < 0 || b > m) continue;  //格点是边数+1 注意边界
            int ga = x + ix[i], gb = y + iy[i];
            int w =( g[ga][gb] != cs[i] );
            int d = dist[x][y] + w;
            if(d <= dist[a][b]) {
                dist[a][b] = d;
                if(!w) q.push_front({a, b});
                else q.push_back({a, b});
            }
        }
    }
    
    return -1;  //不会被执行到
}

int main(){
    int t; scanf("%d", &t);
    // while(t --){
    //     scanf("%d%d", &n, &m);
    //     if((n + m) & 1) 
    //         puts("NO SOLUTION");
    //     else {
    //         for(int i =0 ; i <n; i++) scanf("%s", g[i]);
    //         printf("%d\n", bfs());
    //     }
    // }
    while (t -- )
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i ++ ) scanf("%s", g[i]);

        int t = bfs();

        if (t == 0x3f3f3f3f || t == -1) puts("NO SOLUTION");
        else printf("%d\n", bfs());
    }

    return 0;
}

/*
* @Description: 173. 矩阵距离
* @Author: Xiaobin Ren
* @Date:   2020-10-15 21:16:37
* @Last Modified time: 2020-10-15 21:16:59
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define x first
#define y second

const int N = 1010, M = N * N;
char g[N][N]; //读入没有空格 注意
int n,m;
pii q[M];
int dist[N][N];

//题意就是每个点到最近的1的距离，如果为1自己距离那本身就是0
//多源BFS 求出离每个点最近的起点的距离
//先把所有1入队，然后根据这些点开始向外扩张，最终bfs全图

void bfs(){
    memset(dist, -1, sizeof dist);
    
    int hh = 0, tt = -1; //开始队内没有元素 不能写成tt = 0
    for(int i = 0; i < n;i++)
        for(int j = 0; j < m; j++)
            if(g[i][j] == '1'){
                dist[i][j] = 0;  //先把所有是1的点入队 保持距离的单调性
                q[++tt] = {i, j};
            }
            
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0,1,0,-1};
    
    while(hh <= tt){
        auto t = q[hh++];
        for(int i = 0 ; i < 4; i++){
            int a = t.x + dx[i], b = t.y + dy[i];
            if(a < 0 || a >= n || b < 0 || b >= m) continue;
            if(dist[a][b] != -1) continue;
            
            dist[a][b] = dist[t.x][t.y] + 1;
            q[++tt] = {a, b};
        }
    }
}

int main(){
    scanf("%d%d", &n ,&m);
    for(int i = 0 ; i<n; i++) scanf("%s", g[i]);
    
    bfs();
    
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < m; j++)
            printf("%d ", dist[i][j]);

        printf("\n");
    }
    
    return 0;
}
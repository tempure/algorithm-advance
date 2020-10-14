/*
* @Description: 1076. 迷宫问题
* @Author: Xiaobin Ren
* @Date:   2020-10-14 16:26:30
* @Last Modified time: 2020-10-14 16:26:48
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int ,int > pii;
#define x first
#define y second

const int N = 1010, M = N * N;
int g[N][N];
int n;
pii pre[N][N];  //储存路径 当前节点 是由哪一个点转移过来的
pii q[M];


void bfs(int sx, int sy){
    int dx[4] = {-1,0,1,0}, dy[4] = {0,1,0,-1};

    int hh = 0, tt = 0;
    
    q[0] = {sx, sy};
    memset(pre, -1, sizeof pre);
    
    while(hh <= tt){
        pii t = q[hh++];
        for(int i = 0 ; i< 4 ; i++){
            int a = t.x + dx[i], b = t.y + dy[i];
            if(a < 0 || a >= n || b < 0 || b >= n) continue;
            if(g[a][b]) continue; // 1不能走
            if(pre[a][b].x != -1) continue;
            
            q[++tt] = {a, b};
            pre[a][b] = t; //(a,b) 是从t转移过来的
        }
    }
}

int main(){
    scanf("%d", &n);    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);
            
    bfs(n - 1, n - 1); //bfs一次就可以了 反向搜 然后从头输出
    pii end(0, 0);
    
    while(1){
        printf("%d %d\n", end.x, end.y);
        if(end.x == n - 1 && end.y == n - 1) break;
        end = pre[end.x][end.y];
    }
    return 0;
}
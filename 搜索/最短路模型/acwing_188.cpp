/*
* @Description: 188. 武士风度的牛
* @Author: Xiaobin Ren
* @Date:   2020-10-14 21:51:21
* @Last Modified time: 2020-10-14 21:52:01
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define x first
#define y second
const int N = 155, M = N * N;

//flood fill 需要全图bfs 最短路只需要一次bfs即可

int n, m;
char g[N][N];
pii q[M];
bool st[N][N];
int dist[N][N]; //记录次数

int bfs(){
    //日字形的周围的点 共有8个 顺时针对应xy即可
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int sx, sy;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(g[i][j] == 'K')
                sx = i, sy = j;
                
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    memset(dist, -1 ,sizeof dist);
    dist[sx][sy] = 0;
    
    while(hh <= tt){
        auto t = q[hh++];
        for(int i = 0 ; i < 8; i++){
            int a = t.x + dx[i], b = t.y + dy[i];
            if(a < 0 || a >=n || b < 0 || b >= m) continue;
            if(g[a][b] == '*') continue;
            if(dist[a][b] != -1) continue;  //被遍历过了
            if(g[a][b] == 'H') return dist[t.x][t.y] + 1; //已经找到
            
            dist[a][b] = dist[t.x][t.y] + 1;
            q[++tt] = {a,b};
        }
    }
    return -1;  //题目保证有解 所以写不写无所谓 前边已经返回了
}

int main(){
    cin >> m >> n;
    for(int i = 0 ; i< n; i++) cin >> g[i];
    
    cout << bfs() << endl;
    
    return 0;
}

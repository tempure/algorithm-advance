/*
* @Description: 1098. 城堡问题
* @Author: Xiaobin Ren
* @Date:   2020-10-14 12:41:45
* @Last Modified time: 2020-10-14 12:42:17
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define x first
#define y second
typedef pair<int,int> pii;
const int N = 60, M =N * N;

int n, m;
int g[N][N];
pii q[M];
bool st[N][N];

int bfs(int sx, int sy){
    int dx[4] {0, -1, 0, 1}, dy[4] = {-1,0,1,0};
    int hh = 0, tt = 0;
    int area = 0;
    q[0] = {sx, sy};
    st[sx][sy] = true;
    while(hh <= tt){
        pii t = q[hh++];
        area ++;
        for(int i = 0 ; i <4 ;i++){
            int a = t.x + dx[i], b = t.y + dy[i];
            if(a < 0 || a >= n || b < 0 || b >= m) continue;
            if(st[a][b]) continue;
            
            if(g[t.x][t.y] >> i & 1) continue; //是墙
            
            q[++tt] = {a,b};
            st[a][b] = true;
        }
    }

    return area;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0 ; i<n; i++)
        for(int j = 0; j <m; j++)
            scanf("%d", &g[i][j]);
            
    int cnt = 0, area = 0;
    for(int i = 0; i <n; i++)
        for(int j = 0 ; j< m; j++)  
            if(!st[i][j]){
                area = max(area, bfs(i, j));
                cnt ++;
                // cout << cnt << endl;
            }
            
    printf("%d\n%d\n", cnt, area);

    return 0;
}
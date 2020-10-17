/*
* @Description: 1112. 迷宫
* @Author: Xiaobin Ren
* @Date:   2020-10-17 16:47:20
* @Last Modified time: 2020-10-17 16:47:34
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
//dfs只能保证连通性 不能求出以及保证最短路 优点是代码短 时间复杂度都一样 线性搜一次


const int N = 110;
char g[N][N];
bool st[N][N];
int n;
int xa, ya, xb, yb;

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool dfs(int x, int  y){
    
    if(g[x][y] == '#') return 0;  //终点可能是障碍物 这一步要先于下一行判断

    if(x == xb && y == yb) return 1;
    st[x][y] = 1;
    for(int i = 0; i < 4; i++){
        int a = x + dx[i], b = y + dy[i];
        if(a < 0 || a >= n || b < 0 || b >= n) continue;
        if(st[a][b]) continue;
        // if((g[a][b]) == '#') continue;
        
        if(dfs(a, b)) return 1;
    }
    
    return false;
}

int main(){
    int t;
    cin >> t;
    while(t --){
        cin >> n;
        for(int i =0 ;i < n; i++) cin >> g[i];
        memset(st, 0, sizeof st);
        
        cin >> xa >> ya >> xb >> yb;
        
        if(dfs(xa, ya)) puts("YES");  //xa ya能否走到目标点
        else puts("NO");
    }
    return 0;
}
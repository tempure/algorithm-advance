/*
* @Description: 1097. 池塘计数
* @Author: Xiaobin Ren
* @Date:   2020-10-14 11:08:24
* @Last Modified time: 2020-10-14 11:09:37
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define x first
#define y second

const int N = 1010;
typedef pair<int,int> pii;

int n,m;
char g[N][N];
const int M = N * N;
bool st[N][N];
pii q[M];

void bfs(int sx, int sy){
    int hh = 0, tt = 0;  //初始化
    q[0] = {sx, sy};
    st[sx][sy] = true;
    
    while(hh <= tt){
        pii t = q[hh++];
        
        for(int i = t.x - 1; i <= t.x + 1; i++)  //八连通遍历周围
            for(int j = t.y - 1; j <= t.y + 1; j++){
                if(i == t.x && j == t.y) continue;  // 是中心点自己 跳过 已经标记过了 在函数开头
                if(i <0 || i >= n || j <0 || j >=m) continue; // 越界 
                if(g[i][j] == '.' || st[i][j]) continue; //是否已经标记过 以及是否不是水洼
                
                q[++tt] = {i,j};
                st[i][j] = true;
            }
    }
}

int main(){
    scanf("%d%d",&n, &m);
    for(int i = 0; i < n; i++)
        scanf("%s", g[i]);
    
    int cnt = 0;
    for(int i = 0;  i<n; i++)  //逐行bfs 
        for(int j = 0 ; j<m; j++)
            if(g[i][j] == 'W' && !st[i][j]){
                bfs(i, j);
                cnt ++;
            }
            
    printf("%d\n", cnt);
    
    return 0;
}

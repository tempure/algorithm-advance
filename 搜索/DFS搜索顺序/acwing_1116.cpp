/*
* @Description: 1116. 马走日
* @Author: Xiaobin Ren
* @Date:   2020-10-18 11:00:24
* @Last Modified time: 2020-10-18 11:00:38
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//dfs的内部搜索不需要恢复现场
//整体当作状态转移时候 才需要恢复现场

const int N  = 10;
int n,m;
bool st[N][N];
int ans;  

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void dfs(int x, int y, int cnt){
    if(cnt == n * m){
        ans ++;
        return ;
    }
    
    st[x][y] = 1;
    
    for(int i = 0; i < 8; i++){
        int a = x + dx[i], b = y + dy[i];
        if(a < 0 || a >= n || b < 0 || b >= m) continue;
        if(st[a][b]) continue;
        
        dfs(a, b, cnt + 1);
    }
    st[x][y] = 0; //恢复现场  外部搜索
}

int main(){
    int t;
    cin >> t;
    
    while(t--){
        int x, y;
        cin >> n >> m >> x >> y;
        ans = 0;
        dfs(x, y, 1);
        
        cout << ans << endl;
    }
    return 0;
}
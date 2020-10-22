/*
* @Description: 
* @Author: Xiaobin Ren
* @Date:   2020-10-22 21:10:13
* @Last Modified time: 2020-10-22 21:10:39
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

//单源最短路 然后求出距离起点最远的点的路径长度 也就是最晚接受到的点的时间
//如果某个dist是正无穷，那就是非连通 输出-1

//数据范围太小了，直接floyd 代码短 

const int N = 110;
int n, m;
const int INF = 0x3f3f3f3f;
int d[N][N];

int main(){
    
    cin >> n >> m;
    memset(d, 0x3f, sizeof d);
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        d[a][b] = d[b][a] = min(d[a][b], c);  //防止重边
    } 
    
    //floyd
    for(int k = 1; k <= n; k++)
        for(int i = 1;  i <= n; i++)
            for(int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                
    int res = 0;    
    for(int i = 1; i <= n; i++)
        if(d[1][i] == INF){
            res = -1;
            break;
        }
        else res = max(res, d[1][i]);
        
    cout << res << endl;
    
    return 0;
    
}
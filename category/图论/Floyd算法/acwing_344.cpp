#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int INF = -0xcfcfcfcf;
const int N = 110;
int n, m;
int d[N][N], g[N][N];
int pos[N][N]; //从哪个点转移过来的 同时也是环上编号最大的点
int path[N], cnt ;  //path 当前最小环方案


void get_path(int i , int j){ //从i到j环上所有的点
    if(pos[i][j] == 0) return ; //ij直接相连
    int k = pos[i][j];
    get_path(i, k);
    path[cnt++] = k;
    get_path(k, j);
}

int main(){
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    for(int i = 1; i <= n; i++) g[i][i] = 0;
    
    while(m --){
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    
    int res = INF;
    memcpy(d, g, sizeof d);
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= k; i++) //枚举k左右两边的i,j点对 此时k是环上编号最大的点
            for(int j = i + 1; j < k; j++)
                if(1ll * d[i][j] + g[j][k] + g[k][i] < res) { //对于g是INF的情况 可能会爆掉int然后为负值 应该long long
                    res = d[i][j] + g[j][k] + g[k][i];
                    cnt = 0;
                    path[cnt++] = k;
                    path[cnt++] = i;
                    get_path(i, j);  //递归输出ij之间的点
                    path[cnt++] = j;
                }
                
        for(int i =1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(d[i][j] > d[i][k] + d[k][j]){
                    d[i][j] = d[i][k] + d[k][j];
                    pos[i][j] = k; //记录最大的点 也就是分割点
                }
    }
    
    if(res == INF) puts("No solution.");
    else{
        for(int i = 0; i < cnt; i++) cout << path[i] << ' ';
        cout << endl;
    }
    return 0;
}
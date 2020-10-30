#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
//一共有nm - 1 个边 求最小生成树 优先使用 竖边 
//先把所有已有的边加入并查集 然后剩下的边排序
//此题边数太多 有2 * n^2 个边 如果数据过大 排序可能会TLE
//但是此题的边权之后0和1 所以加边先加所有纵边 直接省去排序的步骤 降为线性复杂度


const int N = 1010, M = N * N, K = 2 * N * N;

struct Edge{
    int a, b, w;
}e[K];

int n, m, k;
int ids[N][N]; //二维坐标映射为一维坐标
int p[M];

int find(int x){
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void get_edges(){
    int dx[4] = {-1, 0 ,1, 0}, dy[4] = {0, 1, 0, -1};
    int dw[4] = {1,2,1,2}; //顺时针旋转的边权
    
    //先加纵向边 再加横向边
    for(int z = 0; z < 2; z++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                for(int u = 0; u < 4; u++)
                    if(u % 2 == z){  //z ==0说明u是0和2, z == 1说明u是1和3 这样就起到了先枚举上下 再左右
                        int x = i + dx[u], y = j + dy[u], w = dw[u];
                        if(x && x <= n && y &&  y <= m){
                            int a = ids[i][j], b = ids[x][y];
                            if(a < b) e[k++] = {a, b, w};// 只加一次边 无向边 
                        }
                    }
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n * m; i++) p[i] = i;
    
    for(int i = 1,  t = 1; i <= n; i++)
        for(int j = 1; j <= m; j++, t++)
            ids[i][j] = t;
            
    int x1, y1, x2, y2;
    
    while(cin >> x1>> y1 >> x2 >> y2){ //加入所有已经有的边到并查集
        int a = ids[x1][y1], b = ids[x2][y2];
        p[find(a)] = find(b);
    }
    
    get_edges();
    
    int res = 0;
    for(int i = 0; i < k; i++){
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if(a != b){
            p[a] = b;
            res += w;
        }
    }
    
    cout << res << endl;
    
    return 0;
}
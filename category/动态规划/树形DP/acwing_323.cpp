/*
* @Description: 323. 战略游戏
* @Author: Xiaobin Ren
* @Date:   2020-10-04 20:51:01
* @Last Modified time: 2020-10-04 20:51:12
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//原题模型:树中每条边 至少选择一个端点，每个点都有权值(1) 求最小的权值和

//对于每个节点f[i][j] 表示在以i为根的子树中，且点i的状态是j的所有选法
//j是0表示不选 j是1表示选 分类讨论

const int N = 1510;
int n;
int h[N], e[N], ne[N], idx;  //有向边
int f[N][2];
bool st[N];

void add(int a, int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void dfs(int u){
    f[u][1] = 1;
    // f[u][0] = 0;
    for(int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        dfs(j);
        
        f[u][0] += f[j][1];
        f[u][1] += min(f[j][0], f[j][1]);
    }
}

int main(){
    
    while(~scanf("%d", &n)){
        memset(f, 0, sizeof f);
        memset(h, -1, sizeof h);
        idx = 0;
        memset(st, 0, sizeof st);
        
        for(int i = 0 ; i< n; i++){
            int id, cnt;
            scanf("%d:(%d)", &id, &cnt);
            while(cnt --){
                int ver;
                scanf("%d", &ver);
                add(id, ver);
                st[ver] = true;
            }
        }
        
        int root = 0;
        while(st[root]) root ++;
        
        dfs(root);
        
        printf("%d\n", min(f[root][0], f[root][1]));
    }
    
    
    return 0;
}
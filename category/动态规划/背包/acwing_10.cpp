/*
* @Description: 10. 有依赖的背包问题
* @Author: Xiaobin Ren
* @Date:   2020-09-26 21:39:29
* @Last Modified time: 2020-09-26 21:39:42
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 110;
int h[N], ne[N], e[N];
int idx;
int v[N], w[N];
int n, m;
int f[N][N];

void add(int a, int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void dfs(int u){ //遍历u为根的子树
    for(int i = h[u]; ~i; i = ne[i]){
        int son = e[i];
        dfs(e[i]);
        
        // 分组背包
        for(int j = m - v[u]; j >= 0; j--) //循环体积 分组 从大到小
            for(int k = 0; k <= j; k++) //决策
                f[u][j] = max(f[u][j], f[u][j - k] + f[son][k]);
    }    
    //将u加进去
    for(int i = m; i >= v[u]; i--) f[u][i] = f[u][i - v[u]] + w[u];
    for(int i = 0; i < v[u]; i++) f[u][i] = 0; //比root体积小的方案
}


//f[u][j] 表示 u 为root的子树中选 总体积不超过j的方案
int main(){
    
    scanf("%d%d", &n,&m);
    
    memset(h, -1 , sizeof h);
    
    int root;
    
    for(int i =1; i <= n; i++){
        int p;
        scanf("%d%d%d", &v[i], &w[i],&p);
        if(p == -1) root = i;
        else add(p, i); //有向边
        
    }
    
    dfs(root);
    
    printf("%d\n", f[root][m]);
    
    return 0;
}

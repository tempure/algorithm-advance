/*
* @Description: 1074. 二叉苹果树
* @Author: Xiaobin Ren
* @Date:   2020-10-04 19:05:24
* @Last Modified time: 2020-10-04 19:05:35
*/
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

//依赖背包的简化版本
//Q就是背包容量 边的值转化为点的值 体积为1 依赖：每个点保留，则父节点要先保留才可以

//f[i][j] 表示i为根的子树 选j个树枝的最大价值

const int N = 110, M = 2 * N;
int n , m;
int h[N], ne[M], e[M], idx, w[M];
int f[N][N];

void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u, int father){ //无向图，存父节点 防止反向dfs
    for(int i = h[u]; ~i; i = ne[i]){ //每个子树当作一个物品组 分组背包 每个节点有2个物品组 二叉树
        if(e[i] == father) continue;
        dfs(e[i],u);
        for(int j = m; j >= 0; j--)  // 体积
            for(int k = 0; k < j; k++) 
            //从子树中最多只能选j-1个树枝 因为子树的根和父节点 还有一个连通树枝要保留
                f[u][j] = max(f[u][j], f[u][j - k - 1] + f[e[i]][k] + w[i]);
    }
}

int main(){
        
    cin >> n >> m;
    
    memset(h, -1, sizeof h);
    
    for(int i = 0 ; i< n - 1; i++){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);   
    }
    dfs(1,-1);
    
    cout << f[1][m] << endl;
     
    return 0;
}
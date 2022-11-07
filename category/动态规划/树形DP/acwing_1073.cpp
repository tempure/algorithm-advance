/*
* @Description: 1073. 树的中心 
* @Author: Xiaobin Ren
* @Date:   2020-10-04 11:00:59
* @Last Modified time: 2020-10-04 11:01:52
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//求出每个点到其他所有点的最远距离 然后取最小的一个 就是中心
//做2次dfs  从上往下 然后从下向上 
//向下的最长就是直接dfs 向上的，如果最长的经过子节点就选次长的，不经过子节点就选择最长的
//每个点距离最远的距离就是max(up[i], down[i])

const int N = 10010, M = 2 * N, INF = 0x3f3f3f3f;
int h[N], e[M], ne[M], idx, w[M];
int d1[N], d2[N];  //d1[] 表示向下走的最长的路径, d2[] 表示向下走的第二长度的路径
int up[N]; //向上走的最长路径
int p1[N], p2[N];
int n;

void add(int a, int b, int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++;
}

int dfs_d(int u, int father){ //向下搜索
    d1[u] = d2[u] = -INF; //最长距离和次长距离
    for(int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        if(j == father)  continue;
        int d = dfs_d(j, u) + w[i];
        if(d >= d1[u]){
            d2[u] = d1[u], d1[u] = d;
            p1[u] = j; //父节点，保存路径
        }
        
        else if(d > d2[u]) d2[u] = d, p2[u] = j; //次大值更新
    }
    
    if(d1[u] == -INF){
        d1[u] = d2[u] = 0;
    }
    
    return d1[u];
}

void dfs_u(int u, int father){ //向上搜索
    for(int i =h[u]; ~i; i = ne[i]){
        int j = e[i];
        if(j == father) continue;
        if(p1[u] == j) up[j] = max(up[u], d2[u]) + w[i];
        else up[j] = max(up[u], d1[u]) + w[i];
        
        dfs_u(j, u);
    }
}

int main(){
    
    memset(h, -1, sizeof h);
    cin >> n;
    for(int i = 0 ; i< n; i++){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c); add(b, a, c);
    }
    
    dfs_d(1, -1);
    dfs_u(1, -1);
    
    int res = INF;
    for(int i = 1; i <= n; i++) res = min(res, max(d1[i], up[i]));
    
    cout << res << endl;
    
    return 0;
}
/*
* @Description: 1077. 皇宫看守
* @Author: Xiaobin Ren
* @Date:   2020-10-05 10:48:00
* @Last Modified time: 2020-10-05 10:48:11
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//f[i][0] 点i没有放置 并且被父节点看到的最小花费
//f[i][1] 点i没有放置 并且被子节点看到的最小花费
//f[i][2] 点i放置了的所有方案的最小花费

const int N = 1510; //无向图
int n;  
int h[N], ne[N], e[N], idx, w[N];
int f[N][3];
bool st[N];

void add(int a, int b){
        e[idx] = b, ne[idx] =h[a], h[a] = idx ++;
}

void dfs(int u){
    f[u][2] = w[u];  //放置
    for(int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        dfs(j);
        f[u][0] += min(f[j][1], f[j][2]);
        f[u][2] += min(min(f[j][0], f[j][1]), f[j][2]);
    }
    //更新f[u][1]
    f[u][1] = 1e9;
    for(int i = h[u]; ~i; i = ne[i]){
        int j =e[i];
        f[u][1] = min(f[u][1],f[j][2] + f[u][0] - min(f[j][1],f[j][2]));
    }
}

int main(){
    cin >> n;
    memset(h, -1 ,sizeof h);
    for(int i = 1; i<= n;i ++){
        int id,cost, cnt;
        cin >> id >> cost  >> cnt;
        w[id] = cost;
        while(cnt--){
            int ver;
            cin >> ver;
            add(id, ver);
            st[ver] = true; //标记是不是根节点
        }
    }
    
    int root = 1;
    while(st[root]) root ++;
    
    dfs(root);
    
    cout << min(f[root][1],f[root][2]) << endl;  //root没有父节点
    
    return 0;
}
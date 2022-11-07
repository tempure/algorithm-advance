// dfs 求树上从任意点出发的最长路，边权可以为负值
// 加上 bool vis[] 之后应该就可以求有环的图了，不再局限于树
// 树上求最长路的例题: https://www.acwing.com/problem/content/4709
// 此题代码如下



#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//不用回到源点
//从1号点出发，只有到某个叶子结点的这一条路径可以走1次最后停下
//其余所有的路径都要回到分叉处走2次
//答案就是所有边的权值和 * 2 - 最长路

const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], w[M], ne[M], idx;

void add(int a, int b, int c){
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int dfs(int u, int fa){ //求最长路
    int res = 0;
    for(int i =h[u]; ~i; i= ne[i]){
        int j = e[i];
        if(j ==fa) continue;
        res = max(res, dfs(j, u) + w[i]);
   }
   return res;
}

void solve() {
    int n;
    cin >> n;
    memset(h, -1, sizeof h);
    ll res = 0;
    for(int i = 1; i< n; i++){
        int a, b, c;
        cin >> a >> b >> c;
        add(a,b,c), add(b, a, c);
        res+=c*2;
    } 
    cout << res - dfs(1, -1) << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const int N = 510, M = 2100;
int n = 500, m;
int g[N][N];
int ans[1100], cnt;
int d[N]; //degree

/**
 * 欧拉路径，字典序最小，题目保证一定存在解
 * 直接贪心思路，每个点都先搜编号最小的出边端点，dfs到最后，逆序就是最小的序列
 */

void dfs(int u){
    for(int i =1; i <= n; i++)
        if(g[u][i]){
            g[u][i] --, g[i][u] --;
            dfs(i);
        }
        ans[++cnt] = u;
}

void solve(){
    cin >> m;
    while(m --){
        int a, b;
        cin >> a >> b;
        g[a][b]++, g[b][a]++;
        d[a]++, d[b]++;
    }
    int start = 1;
    //找起点开始dfs
    while(!d[start]) start++;
    for(int i = 1; i<= n; i++)
        if(d[i] & 1){
            start = i;
            break;
        }
    dfs(start);
    for(int i = cnt; i; i --) cout << ans[i] << endl;
}

int main(){
    solve();
    return 0;
}
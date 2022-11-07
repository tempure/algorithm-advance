/*
* @Description: 11. 背包问题求方案数
* @Author: Xiaobin Ren
* @Date:   2020-09-27 15:58:38
* @Last Modified time: 2020-09-27 15:58:47
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1010, mod = 1e9 + 7;
int f[N], g[N];  //g数组记录f[]取到最大 时候的方案数
int n, m;

int main(){
    
    cin >> n >> m;
    memset(f, 0xcf, sizeof f);  
    f[0] = 0;
    g[0] = 1;
    
    for(int i = 0; i < n; i++){
        int v, w;
        cin >> v >> w;
        for(int j = m; j>= v; j--){
            int maxv = max(f[j], f[j - v] + w);
            int cnt = 0;
            if(maxv == f[j]) cnt += g[j];  //不选第i个物品的最优方案数
            if(maxv == f[j - v] + w) cnt += g[j - v];  //选第i个物品的最优方案数 
            
            g[j] = cnt % mod;
            f[j] = maxv;
        }
    }
    
    int res = 0;
    for(int i = 0; i <= m; i++) res = max(res, f[i]);
    
    int cnt = 0; //找出最大的方案数 求和
    for(int i = 0;i <= m; i++)
        if(res == f[i]) cnt = (cnt + g[i]) % mod;
        
    cout << cnt << endl;
    
    return 0;
}

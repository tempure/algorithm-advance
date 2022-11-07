/*
* @Description: 6. 多重背包问题 III
* @Author: Xiaobin Ren
* @Date:   2020-09-22 21:08:17
* @Last Modified time: 2020-09-22 21:08:24
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 20010;

int n, m;
int f[N], q[N], g[N];

//单调队列优化
int main(){
    
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        int v, w, s;
        cin >> v >> w >> s;
        memcpy(g, f, sizeof f);
        for(int j = 0; j < v; j++){
           int hh = 0, tt = -1;  //单调队列
            for(int k = j; k <= m; k+=v){
                if(hh <= tt && q[hh] < k - s * v) hh++;  //滑出 出队
                if(hh <= tt) f[k] = max(f[k], g[q[hh]] + (k - q[hh]) / v * w);
                while(hh <= tt && g[q[tt]] - (q[tt] - j) / v * w <= g[k] - (k - j) / v * w) tt--;
                q[++tt] = k;
            }
        }
    }
    
    cout << f[m]<< endl;
    
    return 0;
    
}
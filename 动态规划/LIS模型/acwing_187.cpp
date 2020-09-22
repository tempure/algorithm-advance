/*
* @Description: 187. 导弹防御系统
* @Author: Xiaobin Ren
* @Date:   2020-09-22 08:55:18
* @Last Modified time: 2020-09-22 08:55:32
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 55;
int f[N];
//dfs暴搜  指数级别 
int n;
int q[N];
int up[N], down[N]; //记录上升和 下降的子序列的 结尾元素

int ans;  //答案

void dfs(int u, int su, int sd){  //u 当前第几个数 su 当前上升子序列个数 sd下降子序列的个数
    
    if(su + sd >= ans) return; //不能把答案更新更小 直接return
    
    if(u == n){
        ans = su + sd;
        return ;
    }
    
    // 1.当前数放入上升子序列中
    int k = 0;
    while(k < su && up[k] >= q[u])k ++; //寻找结尾元素比q[u]小的 一个子序列
    int t = up[k]; 
    up[k] = q[u];
    if(k < su) dfs(u + 1, su, sd); //能放入当前已经有的子序列 
    else dfs(u + 1, su + 1, sd);  //不能放入 要新建一个子序列
    up[k] = t;  //恢复现场
    
    // 2.当前数放入下降子序列中
    k = 0;
    while(k < sd && down[k] <= q[u]) k ++;
    t = down[k];
    down[k] = q[u];
    if(k < sd) dfs(u + 1, su, sd);
    else dfs(u + 1, su, sd + 1);
    down[k] = t;  //恢复现场
    
}

int main(){
    while(cin >> n, n){
      for(int i = 0; i < n; i++) cin >> q[i];
      
      ans = n; //最坏情况每个数 都一个序列
      
      dfs(0, 0, 0);
      
      cout << ans << endl;
    }
    
    
    return 0;
}
/*
* @Description: 423. 采药
* @Author: Xiaobin Ren
* @Date:   2020-09-22 21:51:43
* @Last Modified time: 2020-09-22 21:51:54
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

// 01 背包 f[i][j] = max(f[i - 1][j], f[i - 1][j - v] + w)
// 完全背包 f[i][j] = max(f[i - 1][j], f[i][j - v] + w)   //第二项的i不一样 其余都一样
//优化到1维以后 只有完全背包的体积是从小到大循环 其余都是从大到小循环
//如果是2维 也就是不优化空间 循环顺序没有限制 都可以

//完全背包： 求所有前缀的最大值
//多重背包： 求滑动窗口的最大值 （单调队列优化）
//有依赖的背包： 树形DP

int t, m;
int f[N], v[N], w[N];

int main(){
    cin >> t >> m;
    for(int i = 1; i <= m; i++)
        cin >> v[i] >> w[i];
        
    for(int i = 1; i <= m; i++)
        for(int j = t; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);
            
    cout << f[t] << endl;
    
    return 0;
}


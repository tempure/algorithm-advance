/*
* @Description: 278. 数字组合
* @Author: Xiaobin Ren
* @Date:   2020-09-23 22:34:32
* @Last Modified time: 2020-09-23 22:34:41
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10010;
int f[N];

//01背包变种
//f[i][j] 表示 前i个数里面选得到和为j 的方案数
//转移方程： f[i][j] = f[i - 1][j] + f[i-1][j-v[i]]  //不包括 i 的选法 + 包括i的选法  
int main(){
    
    int n, m;
    cin >> n >> m;
        
    f[0] = 1; // 其余都是0 因为f[0][0] 也是一种方案 其余的都是不合法 所以方案数都是0
    
    for(int i =0 ;i < n;i++) //物品
    {
        int v;
        cin >> v;
        for(int j = m; j >= v; j --)  // 体积
            f[j] += f[j - v];
    }
    
    cout << f[m] << endl;
    
    return 0;
}
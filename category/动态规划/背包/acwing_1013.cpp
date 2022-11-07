/*
* @Description: 1013. 机器分配
* @Author: Xiaobin Ren
* @Date:   2020-09-24 23:27:00
* @Last Modified time: 2020-09-24 23:27:11
*/
#include <iostream>
#include <algorithm>
using namespace std;

// 分组背包+具体方案

const int N = 11, M = 16;
int n, m;
int f[N][M];  //f[i][j] 从前i组中选 总体积不超过 j的方案价值
int w[N][M]; //存储矩阵

int way[N];  //方案

int main(){
    
    scanf("%d%d", &n, &m);
    
    for(int i = 1; i <= n; i++)
        for(int j =1; j <= m; j++)
            scanf("%d", &w[i][j]);
    
    for(int i = 1; i <= n; i++)  //物品 也就是公司
        for(int j = 0; j <= m; j++){
            f[i][j] = f[i - 1][j];  //第i组物品 一个都不选
            for(int k = 1; k <= j; k++)
                f[i][j] = max(f[i][j], f[i- 1][j - k] + w[i][k]);
        }
    cout << f[n][m] << endl;  //最大价值
    
    //求方案 逆推
    int j = m;
    for(int i = n; i >= 1; i--)
        for(int k = 0; k <= j; k++)
            if(f[i][j] == f[i - 1][j - k] + w[i][k]){  //这一层用上一层的推
            
                way[i] = k;
                j -= k;
                break;  //找到了直接退出 
            }
    for(int i = 1; i <= n; i++) cout << i << ' ' <<  way[i] << endl;

    return 0;
}
/*
* @Description: 
* @Author: Xiaobin Ren
* @Date:   2020-09-27 23:50:24
* @Last Modified time: 2020-09-27 23:51:54
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//f[i][j][0]表示在第i天 已经进行了j次交易 且当前正处于第j次交易 当前手中没有股票
//f[i][j][1]表示在第i天 已经进行了j次交易 且当前正处于第j次交易 当前手中有股票
//简而言之 定义为 从无货到有货 是一次新的交易 有货到无货 还算当前的交易 不是新的

const int N = 1e5 + 10;
const int M = 110, INF = 0x3f3f3f3f;
int n, m; //n天 m次交易上限
int w[N];  // 每天的价格
int f[N][M][2];

int main(){
    
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
    
    memset(f, 0xcf, sizeof f);

    for(int i = 0; i <= n; i++) f[i][0][0] = 0; //初始化注意是从0开始 不是1 
    
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<= m; j++){
            //有货无货 2种情况 分类 状态机 转移 决策
            f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1] + w[i]);
            f[i][j][1] = max(f[i - 1][j][1], f[i - 1][j - 1][0] - w[i]);
        }
    
    int res = 0;    
    for(int i = 1; i <= m; i++) res = max(res, f[n][i][0]);  //最后手中无货
    
    printf("%d\n", res);
    
    return 0;
}
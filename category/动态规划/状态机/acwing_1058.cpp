/*
* @Description: 1058. 股票买卖 V
* @Author: Xiaobin Ren
* @Date:   2020-09-28 23:56:52
* @Last Modified time: 2020-09-28 23:57:00
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//f[i][0] 表示第i天 手中有货 f[i][1] 表示 手中无货的第一天 f[i][2] 表示手中无货的第二天
//f[][] 表示的是收益

const int N = 1e5 + 10;
int f[N][3];
int w[N];

int main(){
    
    int n;
    scanf("%d", &n);
    
    for(int i = 1;i <= n; i++) scanf("%d", &w[i]);
    
    f[0][2] = 0; //状态机 入口 选择无货的第二天 收益最大
    f[0][1] = f[0][0] = 0xcfcfcfcf; //初始化 
    
    for(int i = 1; i <= n; i++){
        f[i][0] = max(f[i - 1][0], f[i - 1][2] - w[i]);
        f[i][1] = f[i - 1][0] + w[i];
        f[i][2] = max(f[i - 1][1], f[i - 1][2]);
    } 
    
    printf("%d\n", max(f[n][1], f[n][2])); // 最优解在1 2 产生，因为手中有货肯定不是最优 还不如不买
    //之所以要在1，2取max， 是因为边界情况 可能一笔也不买 直接在开始就停了 那么就是0
    return 0;
}
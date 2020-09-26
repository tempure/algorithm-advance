/*
* @Description: 1021. 货币系统
* @Author: Xiaobin Ren
* @Date:   2020-09-26 14:24:00
* @Last Modified time: 2020-09-26 14:24:12
*/
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 3010;
//完全背包 求方案数问题
ll f[N];

int a[20];

int main(){
    int n, m;
    f[0] = 1;
    scanf("%d%d", &n, &m);

    for(int i = 0; i < n; i++) scanf("%d", &a[i]);    
    
    for(int i= 0; i < n;i ++){
        int w = a[i];
        for(int j = w; j <= m; j++) 
            f[j] = f[j] + f[j - w];
    }
    
    printf("%lld\n", f[m]);
    
    return 0;
}
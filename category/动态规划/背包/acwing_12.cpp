/*
* @Description: 12. 背包问题求具体方案
* @Author: Xiaobin Ren
* @Date:   2020-09-24 14:58:49
* @Last Modified time: 2020-09-24 14:58:58
*/
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N = 1010;
int n, m;
int v[N], w[N];
int f[N][N];

int main(){
    
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d%d", & v[i], &w[i]);
    
    for(int i = n; i >= 1; i--){
        for(int j = 0 ;j <=m; j++){  //2维 循环顺序无所谓 不优化空间
            f[i][j] = f[i + 1][j];
            if(j >= v[i]) f[i][j] = max(f[i][j], f[i + 1][j - v[i]] + w[i]);
        }
    }
    //f[1][m] 是最最大价值
    int j = m;
    for(int i = 1; i <= n; i++)
        if(j >= v[i] &&  f[i][j] == f[i + 1][j - v[i]] + w[i]){  //相等 能选就必选 才使字典序最小
            printf("%d ", i);
            j -= v[i];
        }
    
    return 0;
}
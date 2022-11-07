/*
* @Description: 1027. 方格取数
* @Author: Xiaobin Ren
* @Date:   2020-09-19 22:47:46
* @Last Modified time: 2020-09-20 20:37:31
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 15;
int w[N][N];
int f[2 * N][N][N];
int a,b,c;
int n;
//思路： 只有当i1 + j1 == i2 + j2 的时候才有可能走到重合的点
//然后重合时候特判一下就好了 最外层枚举 i + j的和 k
int main(){
    cin >> n;
    while(cin >> a >> b >> c && a)
        w[a][b] = c;
    
    for(int k = 2; k <= n + n; k++) //k 从1 + 1 开始
        for(int i1 = 1; i1 <= n; i1++)
            for(int i2 = 1; i2 <= n; i2 ++){
                int j1 = k - i1, j2 = k - i2;
                if(j1 >= 1 && j1 <= n && j2 >= 1 && j2 <= n){
                    int t = w[i1][j1]; //重合就只加一次 
                    if(i1 != i2) t += w[i2][j2];  //不重合 就加上 
                    int &x = f[k][i1][i2];
                    x = max(x, f[k - 1][i1 - 1][i2 - 1] + t);  // 下 下
                    x = max(x, f[k  -1][i1 - 1][i2] + t);  //下 右
                    x = max(x, f[k - 1][i1][i2 - 1] + t);// 右下
                    x = max(x, f[k - 1][i1][i2] + t); //下下
                }
            }
    cout << f[n + n][n][n] << endl;
    return 0;
}
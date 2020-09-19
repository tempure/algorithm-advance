/*
* @Description: 1018. 最低通行费
* @Author: Xiaobin Ren
* @Date:   2020-09-19 22:15:02
* @Last Modified time: 2020-09-19 22:31:32
*/
#include<iostream>
#include <algorithm>
using namespace std;

const int N = 110;
int a[N][N], f[N][N];

int n;

int main(){
    
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> a[i][j];
            
    f[1][1] = a[1][1];
    
    //处理边界 最上面一行 最左一列        
        for(int i = 2; i<= n; i++)
            f[1][i] = a[1][i] + f[1][i - 1];
        for(int i = 2; i <= n; i++)
            f[i][1] = a[i][1] + f[i - 1][1];
            
    for(int i = 2; i <= n; i++)
        for(int j = 2; j <= n; j++)
            f[i][j] = a[i][j] + min(f[i - 1][j], f[i][j - 1]);
            
    cout << f[n][n] << endl;
    
    return 0;
}
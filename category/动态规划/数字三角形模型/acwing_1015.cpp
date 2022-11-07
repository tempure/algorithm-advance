/*
* @Description: 1015. 摘花生
* @Author: Xiaobin Ren
* @Date:   2020-09-19 20:46:05
* @Last Modified time: 2020-09-19 22:11:41
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 110;
int a[N][N], f[N][N];

int r, c, t, m;

int main(){
    cin >> t;
    while(t--){
        memset(f,0xcf,sizeof f);
        cin >> r >> c;
        for(int i = 1; i <= r;i++)
            for(int j = 1; j <= c; j++)
                cin >> a[i][j];
        
        f[1][1] = a[1][1];
        
        //处理边界 最上面一行 最左一列        
        for(int i = 2; i<= c; i++)
            f[1][i] = a[1][i] + f[1][i - 1];
        for(int i = 2; i <= r; i++)
            f[i][1] = a[i][1] + f[i - 1][1];
        //计算
        for(int i = 2; i <= r; i++)
            for(int j = 2; j <= c; j++)
                 f[i][j] = a[i][j] + max(f[i - 1][j], f[i][j - 1]);
            
        cout << f[r][c] << endl;
    }
    
    return 0;
}
/*
* @Description: 321. 棋盘分割
* @Author: Xiaobin Ren
* @Date:   2020-10-02 16:39:19
* @Last Modified time: 2020-10-02 16:39:33
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

//二维区间DP

const int N = 15, M = 9;
const double INF = 1e9;
int n, m = 8;
int s[M][M];
double f[M][M][M][M][N];
double X; //平均数


double get(int x1, int y1, int x2, int y2){
    double sum = s[x2][y2] - s[x2][y1 -1] - s[x1-1][y2] + s[x1 -1][y1-1] - X;//(xi连加减去平均数)
    return sum * sum / n;
}

double dp(int x1, int y1, int x2, int y2, int k){
    double & v = f[x1][y1][x2][y2][k];
    if(v >= 0) return v; //记忆化搜索 被算过 就直接返回
    if(k == 1) return v = get(x1, y1, x2, y2); // 不能再切了 最小了
    
    v = INF;
    for(int i = x1; i < x2; i++){ //横切
        v = min(v, dp(x1,y1,i,y2,k -1) + get(i + 1, y1, x2, y2)); //选上面
        v = min(v, dp(i + 1, y1, x2, y2,k-1) + get(x1,y1,i,y2)); //选下边
    }
    
    for(int i = y1; i < y2; i++){
        v = min(v, dp(x1, y1,x2,i,k-1) + get(x1,i+1,x2,y2));
        v = min(v, dp(x1,i+1,x2,y2,k-1) + get(x1, y1,x2,i));
    }
}

int main(){
    
    cin >> n;
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= m; j++){
            cin >> s[i][j];
            s[i][j] += s[i -1][j] + s[i][j - 1] - s[i-1][j-1];
        }
    memset(f, -1 ,sizeof f); //double 全为-1就是-INF 
    X =(double)s[m][m] / n; //注意转为浮点数取法
    printf("%.3lf\n", sqrt(dp(1,1,8,8,n)));
    return 0;
}
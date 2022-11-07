/*
* @Description: 524. 愤怒的小鸟
* @Author: Xiaobin Ren
* @Date:   2020-09-30 18:54:15
* @Last Modified time: 2020-09-30 21:34:44
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
//两个点确定一个抛物线 问题转换为：给定很多抛物线 问需要多少抛物线最少 覆盖所有的点
//也就是重复覆盖问题 可以用dancing links 此处使用状压DP也能 做

typedef pair<double, double> pii;
#define x first
#define y second

const int N = 18, M = 1 << 18;
const double eps = 1e-6;
int n, m;
pii q[N];
int path[N][N]; //path[i][j] 表示i j两个猪决定的抛物线 能覆盖的点的state 是一个二进制数
int f[M]; //f[state] 表示 state状态下需要的最少的抛物线

int cmp(double x, double y){
    if(fabs(x - y) < eps) return 0;
    if(x < y) return -1;
    return 1;  // x > y
}

int main(){
    
    int t;
    cin >> t;
    while(t --){
        cin >> n >> m;
        for(int i = 0; i < n; i++) cin >> q[i].x >> q[i].y ;
        
        memset(path, 0, sizeof path);
        
        //预处理path 也就是 所有每2个点决定的抛物线 能覆盖的列的状态
        for(int i = 0; i  < n; i++){
            path[i][i] = 1 << i; // 只有一个点的特殊数据 规定为自己覆盖自己
            for(int j = 0; j < n; j++){ //枚举所有的点 
                double x1 = q[i].x, y1 = q[i].y;
                double x2 = q[j].x, y2 = q[j].y;
                
                if(!(cmp(x1, x2))) continue; //x1 x2 相同 就不能确定抛物线 直接换下一对
                
                double a = (y1/x1 - y2/x2) / (x1 - x2);  //方程的系数 a b 来确定抛物线
                double b = (y1/x1) - a * x1;
                
                if(a >= 0) continue; //这一步一定要特判 抛物线一定要开口向下
        
                int state = 0;
                for(int k = 0; k < n; k++){ //枚举由a b确定的抛物线 能覆盖的点
                    double x = q[k].x, y = q[k].y;
                    if(!cmp(a * x * x + b * x, y)) state += 1 << k;
                }
                path[i][j] = state;  //i j 确定的抛物线 能覆盖的所有点组成的状态
            }
        }
        memset(f, 0x3f, sizeof f);
        f[0] = 0;
        
        for(int i = 0; i < (1 << n) - 1; i++){ // （1 << n） - 1就是全是1 的状态
            int x = 0;
            for(int j = 0; j < n; j++)
                if(!(i >> j & 1)){
                    x = j;  //找到任意一个没有被覆盖的列 x
                    break;
                }
                //然后枚举所有能覆盖掉x列的抛物线
            for(int j = 0; j < n; j++)
                f[i | path[x][j]] = min(f[i | path[x][j]], f[i] + 1);
        }
        
        cout << f[(1 << n) - 1] << endl;
    }
    
    return 0;
}
/*
* @Description: 1091. 理想的正方形
* @Author: Xiaobin Ren
* @Date:   2020-10-11 23:48:15
* @Last Modified time: 2020-10-11 23:48:49
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1010;
int n ,m , k;
int w[N][N];
int row_max[N][N], row_min[N][N];
int q[N];

//思路: 二维单调队列 滑动窗口 
//对于每一行，每个点存储的是 当前位置结尾 长度为窗口k的最值 每个窗口的最值存储在最后一列
//先求一次行的窗口最值 然后枚举列 对于每一列 再做一次滑动窗口 这样正方形的右下角元素就是最值

//函数作用：在tot长度的a序列中，求出窗口为k长度的 每个窗口的最小值，然后存入b数组
void get_min(int a[], int b[], int tot){
    int hh = 0, tt = -1;
    for(int i = 1; i <= tot; i++){ //i为窗口结尾 不是窗口外的 注意边界
        if(hh <= tt && q[hh] <= i - k) hh++;
        while(hh <= tt && a[q[tt]] >= a[i]) tt--;
        q[++tt] = i;
        b[i] = a[q[hh]];  
    }
}

void get_max(int a[], int b[], int tot){
    int hh = 0, tt = -1;
    for(int i = 1; i <= tot; i++){
        if(hh <= tt && q[hh] <= i - k) hh++;
        while(hh <= tt && a[q[tt]] <= a[i]) tt--;
        q[++tt] = i;
        b[i] = a[q[hh]]; //存在窗口的最后一个位置上
    }
}

int main(){
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            scanf("%d", &w[i][j]);
    
    //行
    for(int i = 1; i <= n; i++){
        get_min(w[i], row_min[i], m);  //获取最小值 长度为m  
        get_max(w[i], row_max[i], m);  //最大值
    }
    
    int res = 1e9;
    int a[N], b[N], c[N]; //c最大值 b最小值
    
    //列
    for(int i = k; i <= m; i++){
        for(int j = 1; j <= n; j++) a[j] = row_min[j][i]; 
        //把当前第i列的每一行的窗口最小值 存入a数组  然后在a数组再求一次滑动窗口
        get_min(a, b , n);
        
        for(int j = 1; j <= n; j++) a[j] = row_max[j][i];
        get_max(a, c, n);
        
        //枚举行的时候 枚举列 也就是正方形的右下角元素 储存着最值
        for(int j = k; j <= n; j++) res = min(res, c[j] - b[j]);
    }
    
    printf("%d\n", res);
    
    return 0;
}

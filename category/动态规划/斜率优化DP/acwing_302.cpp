/*
* @Description: 302. 任务安排3
* @Author: Xiaobin Ren
* @Date:   2020-10-13 19:46:23
* @Last Modified time: 2020-10-13 19:46:31
*/
#include <iostream>
#include <algorithm>
using namespace std;

//t可以是负数 斜率不再有单调性 但是横坐标递增 查询斜率只能二分
//维护队尾凸包 方法不变 复杂度O(n ^ logn)

const int N = 300010;
int n, s;
double t[N], c[N];  //会爆long long 
double  f[N];
int q[N];

int main(){
    scanf("%d%d", &n, &s);
    for(int i = 1; i <= n; i++){
        cin >> t[i] >> c[i];
        t[i] += t[i-1];
        c[i] += c[i-1];
    }
    int hh = 0, tt = 0;
    q[0] = 0;
    
    for(int i = 1; i <=n; i++){
        //二分斜率
        int l = hh, r = tt;
        while(l < r){
            int mid = l + r >> 1;
            if(f[q[mid + 1]] - f[q[mid]] > (c[q[mid + 1]] - c[q[mid]]) * (t[i] + s)) r = mid;
            else l = mid + 1;
            
        }
        
        int j = q[r];
        f[i] = f[j] - (t[i] + s) * c[j] + t[i] * c[i] + s * c[n];
        
        //维护队尾的凸包
        while(hh < tt && (f[q[tt]] - f[q[tt-1]]) * (c[i] - c[q[tt]]) >= (f[i] - f[q[tt]]) * (c[q[tt]] - c[q[tt-1]])) tt--;
        q[++tt] = i; 
    }
    
    printf("%.0lf\n", f[n]);
    
    return 0;
}
/*
* @Description: 301. 任务安排2
* @Author: Xiaobin Ren
* @Date:   2020-10-12 22:00:14
* @Last Modified time: 2020-10-12 22:00:27
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
/*
    数据范围加大 不能朴素N ^ 2
    需要斜率优化 也叫凸包优化
    查找凸包的下界时候 可以直接二分 找出大于等于当前斜率的第一个点 
    但是此题特殊 直线的斜率为正 且点的横坐标递增 且含有前缀和 
    所以斜率也是单调递增的 所以可以线性求出 总体复杂度O(N)
    在加点的过程中同时维持凸包 用队列维护
    队头所有斜率小于当前斜率的点删掉 队尾不在凸包上的点删掉 其实就是格雷厄姆算法 
*/

//f[i] = min{f[j] + sumt[i]*(sumc[i] - sumc[j]) + s * (sumc[n] - sumc[j])}
//移项得到 f[j] = (sumt[i] + s) * sumc[j] + f[i] - sumt[i] * sumc[i] - s * sumc[n]
// f[j] 就是因变量 y, sumc[j] 就是自变量x  斜率是 sumt[i] + s 
//当i固定的时候 截距是f[i]  - sumt[i] * sumc[i] - s * sumc[n]
//目的就是让截距中的f[i]最小 


const int N = 300010;
int n, s;
ll c[N], t[N];
int q[N];
ll f[N];

int main(){
    cin >> n >> s;
    for(int i = 1; i <= n; i++){
        cin >> t[i] >> c[i];
        t[i] += t[i-1];
        c[i] += c[i-1];
    }
    f[0] = 0;  
    int hh = 0, tt = 0;
    q[0] = 0;
    for(int i = 1; i <= n; i++){
        //队列中至少要2个元素 所以是hh < tt  维护队头
        while(hh < tt && (f[q[hh + 1]] - f[q[hh]]) <= (t[i] + s) * (c[q[hh + 1]] - c[q[hh]])) hh++; 
        int j = q[hh];
        f[i] = f[j] - (t[i] + s) * c[j] + t[i] * c[i] + s * c[n];
        
        //维护队尾 队尾最后2个点的斜率大于当前点和队尾点的斜率 那么就队尾弹出 然后加入新的 维护凸包
        while(hh < tt && (f[q[tt]] - f[q[tt-1]]) * (c[i] - c[q[tt]]) >= (f[i] - f[q[tt]]) * (c[q[tt]] - c[q[tt-1]])) tt--;
        q[++tt] = i;
    }
    cout << f[n] << endl;
    
    return 0;
}
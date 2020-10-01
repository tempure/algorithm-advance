/*
* @Description: 320. 能量项链
* @Author: Xiaobin Ren
* @Date:   2020-10-01 17:11:23
* @Last Modified time: 2020-10-01 17:11:36
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 210;
int f[N][N];
int w[N];
const int INF = 0x3f3f3f3f;

int n;
//用一个数字 以及收尾来代替整个序列 比如2 3 5 10 表示为2 3 5 10 2
//然后环形 加倍 拼接 解决
//转移方程：f[l][r] = max(f[l][r], f[l][k] + f[k][r] + w[l] * w[k] * w[r]); k是分割点
int main(){
    
    cin >> n;
    
    for(int i= 1; i <= n; i++){
        cin >> w[i];
        w[n + i] =w[i];
    }
    
    for(int len = 3; len <= n + 1; len ++)  //长度为2只有一个珠子不能释放 n+1是因为要回到最初的尾节点
        for(int l = 1; l + len - 1 <= n * 2; l++){
            int r = l + len - 1;
            for(int k = l + 1; k < r; k++) // 枚举分割的点
                f[l][r] = max(f[l][r], f[l][k] + f[k][r] + w[l] * w[k] * w[r]);
        }
    int res = 0;
    for(int i = 1; i <= n; i++) res = max(res, f[i][i + n]);  //枚举长度为n + 1 的区间
    
    cout << res << endl;
    
    return 0;
}
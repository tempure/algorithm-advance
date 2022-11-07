/*
* @Description: 300. 任务安排1
* @Author: Xiaobin Ren
* @Date:   2020-10-12 18:41:01
* @Last Modified time: 2020-10-12 18:41:10
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//将每个s对后边的影响 全部算到当前的区间 提前算
//f[i] = min{f[j] + sum[ti]*(sum[ci] - sum[cj]) + s * (sum[cn] - sum[cj])}
//状态划分 就是最后  此题不需要斜率优化 5000数据的 复杂度就可以过掉 N ^ 2复杂度

const int N = 5010;
int n, s;
int sumt[N], sumc[N];
int f[N];

int main(){
    cin >> n >> s;
    for(int i = 1; i<=n; i++){
        int t,c;
        cin >> t >> c;
        sumt[i] = sumt[i-1] + t;
        sumc[i] = sumc[i-1] + c;
    }
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 0; j < i; j++) //枚举前一个划分的位置
            f[i] = min(f[i], f[j] + sumt[i] * (sumc[i] - sumc[j]) + s * (sumc[n] - sumc[j]));
    
    cout << f[n] << endl;
    
    return 0;
}

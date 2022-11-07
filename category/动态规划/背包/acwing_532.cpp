/*
* @Description: 532. 货币系统
* @Author: Xiaobin Ren
* @Date:   2020-09-26 16:30:16
* @Last Modified time: 2020-09-26 16:30:27
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int T;
//判断方案数是否为0问题 完全背包
//性质：b[]中的数 全部来自于a[]中 问题转化为 a[]中能被别的a[i]表示的数全部筛掉
//等价的问题是 一个数a[i] 能不能被比其小的数的和表示 如果表示方案为0 则留下
//剩下的就是 最后的 极大独立集

const int N = 25010;
int f[N];
int a[110];

int n, m;

int main(){
    int t;
    scanf("%d", &t);
    while(t --){
        scanf("%d", & n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        sort(a, a + n);
        
        memset(f, 0, sizeof f);
        f[0] = 1;
        int res = 0;
        for(int i = 0; i < n; i++){
            if(!f[a[i]]) res ++;
            for(int j = a[i]; j <= a[n - 1]; j++)
                f[j] = f[j] + f[j - a[i]];
        }
        
        printf("%d\n", res);
    }
    return 0;
}
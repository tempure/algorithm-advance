/*
* @Description: 1087. 修剪草坪
* @Author: Xiaobin Ren
* @Date:   2020-10-11 21:46:26
* @Last Modified time: 2020-10-11 21:46:35
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int n, m;
int q[N];
ll ans, f[N];
//每k + 1个里必须不选 1 个，使不选的总效率最小，最后用总效率减去不选的效率即可
//和《烽火传递》是同一个题 没有区别
//所以就是每k+1个里面必选一个，然后用所有的和 减去 就是最大的效率值
int main(){
    scanf("%d%d", &n ,&m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &f[i]);
        ans += f[i];
    }
    
    int tt = 0 , hh = 0;
    for(int i = 1; i <= n; i++){
        if(i - q[hh] > m + 1) hh++;
        f[i] += f[q[hh]];
        while(hh <= tt && f[q[tt]] >= f[i]) tt--;
        q[++tt] = i;
    }
    
    ll res = 1e18 + 7;
    
    for(int i = n - m; i <= n; i++) res = min(res, f[i]);
    
    cout << ans - res << endl;
    
    return 0;
}
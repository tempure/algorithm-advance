/*
* @Description: 1089. 烽火传递
* @Author: Xiaobin Ren
* @Date:   2020-10-11 15:34:25
* @Last Modified time: 2020-10-11 15:34:32
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 200010;
int w[N], f[N], q[N];
int n, m;

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> w[i];
    int hh = 0, tt = 0; //有一个元素 就是tt = 0 没有就是tt = -1
    f[0] = 0;
    for(int i = 1; i <= n; i++){
        if(q[hh] < i - m) hh ++;
        f[i] = f[q[hh]] + w[i];
        while(hh <= tt && f[q[tt]] >= f[i]) tt--;
        q[++tt] = i;
    }
    
    int res = 1e9;
    for(int i = n - m + 1; i <= n; i++) res = min(res, f[i]);
    
    cout << res << endl;
    
    return 0;
}
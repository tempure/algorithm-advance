/*
* @Description: 1019. 庆功会
* @Author: Xiaobin Ren
* @Date:   2020-09-23 22:48:54
* @Last Modified time: 2020-09-23 23:19:08
*/
#include <iostream>
#include <algorithm>
using namespace std;

//裸多重背包 朴素版复杂度 n * m * (s + 1) //加上0
//3e7 可以过 不用单调队列优化

const int N = 6010;
int n, m;
int f[N];

int main(){
    
    cin >> n >> m;
    
    for(int i = 0; i < n; i++){  //物品
        int v, w, s;
        cin >> v >> w >> s;
        for(int j = m; j >= v; j--) //体积 注意多重背包循环可以直接减到0 (j >= 0) 
            for(int k = 0; k <= s && k * v <= j; k++) //每种物品的个数 
            f[j] = max(f[j], f[j - k * v] + k * w);
    }
    
    cout << f[m] << endl;
    
    return 0;
}
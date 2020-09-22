/*
* @Description: 1024. 装箱问题
* @Author: Xiaobin Ren
* @Date:   2020-09-22 22:15:59
* @Last Modified time: 2020-09-22 22:16:10
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 20010;
int v, n;
int f[N];
//将每个箱子的体积也认为等于其价值
//体积不超过总体积的情况下 箱子总体积时多少
int main(){
    
    cin >> v >> n;
    for(int i = 0; i < n; i++){
        int w; cin >> w;
        for(int j = v; j >= w; j--) f[j] = max(f[j], f[j - w] + w);
    }
    
    cout << v - f[v] << endl;
    
    return 0;
}
/*
* @Description: 426. 开心的金明
* @Author: Xiaobin Ren
* @Date:   2020-09-26 13:36:38
* @Last Modified time: 2020-09-26 13:36:49
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int M = 30010;
int f[M];

int n, m;

int main(){
    
    cin >> m >> n;
    
    for(int i = 1;i <= n; i++){
        int v ,w ;
        scanf("%d%d", &v, &w);
        for(int j = m; j >= v; j--)
            f[j] = max(f[j], f[j - v] + v * w);
    }
    
    cout << f[m] << endl;
    
    return 0;
}
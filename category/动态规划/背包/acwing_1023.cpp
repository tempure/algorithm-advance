/*
* @Description: 1023. 买书
* @Author: Xiaobin Ren
* @Date:   2020-09-24 12:03:03
* @Last Modified time: 2020-09-24 12:03:13
*/
#include <iostream>
#include <algorithm>
using namespace std;

//注意此题一定要花费所有的金额才可以
//裸完全背包
const int N = 1010;

int v[4] = {10, 20, 50, 100};
int f[N];

int main(){
    
    int m;
    cin >> m;
    
    f[0] = 1;  
    
    for(int i = 0; i < 4; i++)
        for(int j = v[i]; j <= m; j++)
            f[j] = f[j] + f[j - v[i]];
    
    cout << f[m] << endl;
    
    return 0;
}
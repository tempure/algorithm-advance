/*
* @Description: 8. 二维费用的背包问题
* @Author: Xiaobin Ren
* @Date:   2020-09-23 09:58:08
* @Last Modified time: 2020-09-23 09:58:17
*/
#include <iostream>
#include <algorithm>
using namespace std;

int N, V, M;
const int P = 110;
int f[P][P];

int main(){
    
    cin >> N >> V >> M;
    
    for(int i = 0 ; i < N; i++){  //物品
        int v, m, w;
        cin >> v >> m >> w;
        for(int j = V; j >= v; j--)  //体积
            for(int k = M; k >= m; k--)
                f[j][k] = max(f[j][k], f[j - v][k - m] + w);  //决策 注意加上w价值
    }
    
    cout << f[V][M] << endl;
    
    return 0;
}
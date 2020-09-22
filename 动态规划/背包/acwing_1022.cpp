/*
* @Description: 1022. 宠物小精灵之收服
* @Author: Xiaobin Ren
* @Date:   2020-09-22 23:28:58
* @Last Modified time: 2020-09-22 23:29:10
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010, M = 510;

//二维费用背包 同样也可以优化到1维

//f[i][j][k] 表示前i个小精灵选 费用1不超过j 费用2 不超过k 的最大价值 也就是抓到的最多的小精灵数量


int n, V1, V2;
int f[N][M];

int main(){
    
    cin >> V1 >> V2 >> n; //V1 精灵球数量 V2 皮卡丘体力值
    
    for(int i = 0; i < n; i++){  //物品
        int v1, v2;
        cin >> v1 >> v2;
        for(int j = V1; j >= v1; j--)  //体积
            for(int k = V2 - 1; k >= v2; k--)  //体积 从v2 - 1 开始是因为皮卡丘不能ph为0
                f[j][k] = max(f[j][k], f[j - v1][k - v2] + 1); //决策
    }
    
    cout << f[V1][V2 - 1] << ' ';
    
    int k = V2 - 1;
    while(k > 0 && f[V1][k-1] == f[V1][V2 - 1]) k--;
    
    cout << V2 - k << endl;
    
    
    return 0;
}
/*
* @Description: 1020. 潜水员
* @Author: Xiaobin Ren
* @Date:   2020-09-23 16:44:24
* @Last Modified time: 2020-09-23 16:44:58
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;


//二维费用变型  求最大 变为求最小
//也就是 第一维费用>=m 第二维费用>= n ，f[][] 的最小值

const int N = 50, M = 160;
int f[N][M];
int n, m, k;

int main(){
    cin >> n >> m >> k; //n 氧气 m 氮气 
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    
    while(k --){ //物品
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        for(int i = N - 1; i >= 0; i--)  //体积 开到N-1 是因为下标
            for(int j= M - 1; j >= 0; j--)
            /*
                决策解释:
                    为什么上面的代码 j只需要遍历到v，k只能遍历到m。而下面的代码 j还需要遍历到0，k还需要遍历到0 ？
                    同时为什么氧气或者氮气所需的是数量是负数时，可以与数量0的状态等价？

                    解答：对比两题的思路，二维费用的背包问题，求的是不能超过体积V，重量M的情况下，能拿到价值的最大值。
                    而本题是至少需要体积V，重量M的情况下，能拿到价值的最小值。就拿体积来说，至少需要多少体积，
                    也就是说有体积比需要的体积大的物品还是能用得到，例如f[3][5]，至少需要3个体积，5个重量，求能拿到价值的最小值，
                    现在只有一个物品，体积是4，重量是4，价值w，它说至少需要3个体积，那么体积是4还是可以用到，只是多了1个体积没用占着而已，
                    不影响其价值。因此若用了这个物品，则变成了求f[0][1] + w，表示体积已经不再需求了，只需要0个体积即可。

            */
                f[i][j] = min(f[i][j], f[max(0,i - v1)][max(0, j - v2)] + w);
    }
    
    int res = 1e9;
    
    for(int i = n; i < N; i++) //花费要 >= n 第一维
        for(int j = m; j < M; j++)
            res = min(res, f[i][j]);
            
    cout << res << endl;
    
    
    return 0;
}
/*
* @Description: 1068. 环形石子合并
* @Author: Xiaobin Ren
* @Date:   2020-10-01 13:23:50
* @Last Modified time: 2020-10-01 13:24:12
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 410; //开2倍的链长度
const int INF = 0x3f3f3f3f;
int n;
int s[N], w[N];
int f[N][N];  //最小值  f[i][j] 表示合并区间i~j所需要的最小值
int g[N][N];  // 最大值

//朴素的石子合并 一排的 复杂度是n^3
//环形的思路是枚举环上的缺口 然后再用朴素 这样本质是求n-1个 长度为n的链合并 复杂度n^4 要优化

//优化 直接把环形展开 复制一份 2个拼起来 一起 然后在2n长度区间 求区间长度为n的区间即可

int main(){
    cin >> n;
    for(int i = 1;i <= n; i++){
        cin >> w[i];
        w[i + n] = w[i];
    }
    //前缀和
    for(int i = 1; i <= 2 * n; i++) s[i] = s[i - 1] + w[i];
    
    memset(f, 0x3f, sizeof f);
    memset(g, 0xcf, sizeof g);
    
    for(int len = 1; len <= n; len ++) //区间长度
        for(int l = 1;l + len -1 <= n * 2; l++){  //左端点
            int r = l + len - 1; //右端点
            if(len == 1) f[l][r] = g[l][r] = 0;
            else{
                for(int k = l; k < r; k++){  //分界点
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
                g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r] + s[r] - s[l - 1]);
                }
            }
        }
        
    int minv = INF, maxv = -INF;
    //由于是2倍的长度 所以要遍历一次 求出最值
    for(int i = 1;i <= 2 * n; i++){
        minv = min(minv, f[i][i + n - 1]);
        maxv = max(maxv, g[i][i + n - 1]);
    }
    
    cout << minv << endl << maxv << endl;
    
    return 0;
}
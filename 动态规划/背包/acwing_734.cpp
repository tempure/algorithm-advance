/*
* @Description: 734. 能量石
* @Author: Xiaobin Ren
* @Date:   2020-09-27 18:46:01
* @Last Modified time: 2020-09-27 18:46:20
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
//贪心 邻项交换证明 以si/li 从小到大排序
//那么最优的吃的顺序 就是在升序的序列中产生 接着就是01背包
// f[i][j] 表示 取了i个能量石头 总共花费了j时间 的最大能量
const int N  =10010; // N * S 所有能量石总的所有时间
int n;
int f[N];


struct Stone{
    int s, e, l;
    bool operator< (const Stone & w) const{
        return s * w.l < l * w.s; // 排序
    }
}stone[110];

int main(){
    
    int t;
    cin >> t;
    
    for(int c = 1; c <= t; c++){
        int m = 0;
        cin >> n;
        for(int i = 0; i < n; i++){
            int s,e ,l;
            cin >> s >> e >> l;
            stone[i] = {s, e, l};
            m += s; //m 记录总时间（背包总体积）
        }
        
        sort(stone, stone + n);
        memset(f, 0xcf, sizeof f);
        f[0] = 0;
        
        for(int i = 0; i < n; i++){ //物品
            int s = stone[i].s, e = stone[i].e, l = stone[i].l;
            for(int j = m; j >= s; j --) //体积
                //解释：吃完第i个石头的时候，用的总时间是j 那么吃之前 已经过了j - s 时间 然后减去能量即可
                f[j] = max(f[j], f[j - s] + max(0, e - (j - s) * l));
        }
        
        int res = 0;
        for(int i = 0; i <= m; i++) res = max(res, f[i]);
        
        printf("Case #%d: %d\n", c, res);
    }
     
    return 0;
}


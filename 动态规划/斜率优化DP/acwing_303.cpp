/*
* @Description: 303. 运输小猫
* @Author: Xiaobin Ren
* @Date:   2020-10-14 00:11:13
* @Last Modified time: 2020-10-14 00:11:26
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

//f[j][i]  j个饲养员 取了前i只小猫的最小花费
//f[j-1][k] + s[k] = a[i] * k + f[j][i] -a[i] * i + s[i] 
//a[i] 是小猫的结束时间 然后排序 就可以保持a[i] 也就是斜率递增 横坐标递增 线性复杂度

const int N = 100010, M = 100010, P = 110;
int n, m, p;
ll d[N], t[N], a[N], s[N];
ll f[P][M];
int q[M];

ll get_y(int k, int j){
    return f[j-1][k] + s[k];
}

int main(){
    scanf("%d%d%d", &n ,&m, &p);
    for(int i = 2;i <= n; i++){
        scanf("%lld", &d[i]);
        d[i] += d[i-1];
    }
    
    for(int i = 1; i <= m; i++){
        int h;
        scanf("%d%lld", &h, &t[i]);
        a[i] = t[i] - d[h]; // 每只小猫玩耍的时间减去饲养员路上需要花费的时间
    }
    
    sort(a + 1, a + m + 1);
    
    for(int i = 1; i <= m; i++) s[i] = s[i - 1] + a[i];
    
    memset(f, 0x3f, sizeof f);
    
    for(int i = 0; i <= p; i++) f[i][0] = 0;  //i个饲养员 处理0只小猫 都是0
    
    for(int j = 1;  j<= p; j++){
        int hh = 0, tt = 0;
        q[0] = 0;
        for(int i = 1; i <=m; i++){
            while(hh < tt && (get_y(q[hh+1], j) - get_y(q[hh] ,j)) <= a[i] * (q[hh+1] - q[hh])) hh++;
            int k = q[hh];
            f[j][i] = f[j-1][k] - a[i] * k + s[k] + a[i] * i - s[i];
            while (hh < tt && (get_y(q[tt], j) - get_y(q[tt - 1], j)) * (i - q[tt]) >=
                (get_y(i, j) - get_y(q[tt], j)) * (q[tt] - q[tt - 1])) tt -- ;
            q[ ++ tt] = i;
        }
    }
    
    printf("%lld\n", f[p][m]);
    
    return 0;
}

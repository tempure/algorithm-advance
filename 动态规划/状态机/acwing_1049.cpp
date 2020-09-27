/*
* @Description: 1049. 大盗阿福
* @Author: Xiaobin Ren
* @Date:   2020-09-27 23:00:33
* @Last Modified time: 2020-09-27 23:00:43
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 100010;
const int INF = 0x3f3f3f3f;
int n; int w[N], f[N][2];

//状态机：f[i][j] 表示 走了i步 当前处于状态j的所有走法的收益
//  j为0表示不抢下一个位置，也就是位于原地， 1表示抢下个位置，也就是移动
int main(){
    
    int t;
    scanf("%d", &t);
    while(t --){
        memset(f, 0, sizeof f);
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)  scanf("%d", &w[i]);
        f[0][0] = 0; f[0][1] = -INF;  // 走了0步 不能走到状态1 初始就在状态0
        
        for(int i = 1; i <= n; i++){
            //2种当前的状态 分别讨论
            f[i][0] = max(f[i - 1][0], f[i - 1][1]); // 转移到状态0的决策 0->0/ 1->0
            f[i][1] = f[i - 1][0] + w[i]; //转移到状态1的决策 只有0->1
        }
        
        printf("%d\n", max(f[n][0], f[n][1]));
    }
    
    return 0;
}
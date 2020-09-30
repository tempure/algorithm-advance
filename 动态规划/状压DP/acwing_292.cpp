/*
* @Description: 292. 炮兵阵地
* @Author: Xiaobin Ren
* @Date:   2020-09-30 13:25:28
* @Last Modified time: 2020-09-30 13:25:43
*/
#include <iostream>
#include <vector>
using namespace std;

int n, m;
//f[i][j][k] 表示 已经摆完i行 第i - 1 行的状态是j 第i行的状态是k的方案的最大值
//状态的限制条件： 第i-1行是a 第i行是b 第i-2行是c
// 1.((a & b)|(a & c) | (b & c)) == 0 三行不能有交集
// 2.(g[i-1] & a | g[i] & b) == 0 , 2行的炮不能放在山顶上 g[] 存储每一行的状态

//另外此题需要滚动数组来优化空间

const int M = 1 << 10;
int g[110];
int cnt[M];  //每个二进制数中1的个数
vector<int> state;
int f[2][M][M];  //一亿的数组需要400M内存 所以要用滚动数组优化

bool check(int state){
    for(int i = 0; i < m; i++) //连着三个H 就不合法
        if((state >> i & 1) && ((state >> i + 1 & 1|state >> i + 2 & 1)))
            return false;
    return true;
}   

int count(int state){
    int res = 0;
    for(int i =0; i < m; i++) res += state >> i & 1;
    return res;
}

int main(){

    cin >> n >> m;
    for(int i = 1; i<=n;i++)
        for(int j = 0; j < m; j++){
            char c;
            cin >> c;
            if(c == 'H') g[i] += 1 << j; //山地置为1 意思是已经放了炮了 不能再放了
        }
    for(int i = 0; i < 1 << m; i++) //预处理合法状态
        if(check(i)){
            state.push_back(i);
            cnt[i] = count(i);
        }
        
    for(int i = 1; i <= n + 2; i++) //行
        for(int j = 0; j < state.size(); j++) // 第i-1的状态
            for(int k = 0; k < state.size(); k++) //第i行状态
                for(int u = 0; u < state.size(); u ++){//第i-2行状态
                    int a = state[j], b = state[k],c=state[u]; //a表示i-1行状态 b表示第i行状态
                    if((a & b) | (b & c) | (a & c)) continue;
                    if(g[i-1] & a| g[i] & b) continue;
                    //f[i][j][k] 三维都往前推一个 就是f[i-1][u][j]
                    f[i&1][j][k] = max(f[i & 1][j][k], f[i-1 & 1][u][j] + cnt[b]); //滚动数组
                }
    
    cout << f[n + 2 & 1][0][0] << endl;
    
    return 0;
}
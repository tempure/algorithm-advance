/*
* @Description: 327. 玉米田
* @Author: Xiaobin Ren
* @Date:   2020-09-30 11:14:12
* @Last Modified time: 2020-09-30 11:14:22
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int m, n;

const int N = 14, M = 1 << 12, mod = 1e8;
vector<int> state;
int g[N];
vector<int> head[M];  //每个状态能转移来的状态
int f[N][M];

//f[i][s] 表示 摆了i行 第i行的状态是s 的方案集合(数量)
//当前行 只和上一行有关系 和上上行没有关系

bool check(int state){
    return !(state & state >> 1); //O(1) 判断是否有2个相邻的1 
    //如果有 那就返回false
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) //行下标从1开始 因为回出现f[i - 1] 列下标从0开始
        for(int j = 0; j < m; j++){
            int t; cin >> t;
            g[i]  += !t << j; //是0的位置 置为1 表示不能选 方便做&运算
            //这里用一个数 来表示一行的状态 所以每次都加最高位 所以要 << j 来加上
        }
        
    for(int i = 0; i < 1 << m; i++) //  先找出所有合法状态
        if(check(i))
            state.push_back(i);
    
    for(int i = 0; i < state.size(); i++)
        for(int j = 0; j<state.size(); j++){
            int a = state[i], b = state[j];
            if((a & b) == 0) head[i].push_back(j); //j可以转移到i
        }
    f[0][0] = 1;    //初始化 不摆也算一种状态
    for(int i = 1; i<= n + 1; i++) //枚举到n + 1 直接得到答案
        for(int a = 0; a < state.size();a++)
            for(int b : head[a]){
                if(g[i] & state[a]) continue;
                f[i][a] =(f[i][a] + f[i - 1][b]) % mod;
            }
    
    cout << f[n + 1][0] << endl;
    
    return 0;
}
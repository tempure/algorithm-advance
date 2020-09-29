/*
* @Description: 1064. 小国王
* @Author: Xiaobin Ren
* @Date:   2020-09-29 23:25:53
* @Last Modified time: 2020-09-29 23:26:08
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N  =12, M = 1 << 10, K = 110;  //k是国王数量
int n, m;
//f[i][j][s] 表示已经放了前i行 共j个棋子 并且第i行的状态（二进制）是 s 情况下的方案总数
// 设上下两行的状态表示为b和a 则需要满足 (a & b) == 0 并且 (a | b) 不能有2个相邻的1

vector<int> state;
int id[M];  //状态和下标的映射关系
vector<int> head[M];  //每个状态可以转移到的其他状态
long long  f[N][K][M];
int cnt[M];

bool check(int state){
    for(int i = 0 ; i< n; i++)
        if((state >> i & 1) && (state >> i + 1 & 1)) //有2个相邻的1 不合法
            return false;
    return true;
}

int count(int state){  //计算有多少个1 某个状态
    int res = 0;
    for(int i = 0 ; i< n; i++) res += state >> i & 1;
    
    return res;
}

int main(){
    
    cin >> n >> m;
    for(int i = 0; i < 1 << n; i++)
        if(check(i)){
            state.push_back(i); //先筛一下可能合法的状态
            id[i] = state.size() - 1; // id存合法状态下标
            cnt[i] = count(i);
        } 
    for(int i = 0 ; i < state.size(); i++)
        for(int j = 0; j < state.size(); j++){
            int a = state[i], b = state[j];  // 枚举上下2行的状态
            //判断能否2个状态可以转移
            if(((a & b) == 0) && check(a | b)) 
                head[i].push_back(j);  //符合就把b添加到可以转移到a的状态数组中
        }
        
    f[0][0][0] = 1; //没摆 合法方案 
    
    for(int i = 1; i <= n + 1; i++)//行 多一行 便于统计
        for(int j = 0; j <= m; j++) //j是国王数量
            for(int a = 0; a < state.size(); a++) // 所有的状态
                for(int b : head[a]){
                    int c = cnt[state[a]];
                    if(j >= c)
                        f[i][j][a] += f[i - 1][j - c][b];
                }
    cout << f[n + 1][m][0] << endl;
    return 0;
}
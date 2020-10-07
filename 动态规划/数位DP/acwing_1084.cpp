/*
* @Description: 1084. 数字游戏 II
* @Author: Xiaobin Ren
* @Date:   2020-10-07 15:50:10
* @Last Modified time: 2020-10-07 15:50:25
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 15, M = 110;
int f[N][N][M]; //f[i][j][k] i位数 最高位j 模N余数为k

int p; //模数

int mod(int x, int y){  //余数为正 需要自己手写取模函数
    return (x % y + y) % y;
}

void init(){
    
    memset(f, 0, sizeof f);
    
    for(int i = 0; i <= 9; i++) f[1][i][i % p] ++;
    
    for(int i = 2; i < N; i++)
        for(int j =0 ; j<=9; j++)
            for(int k = 0; k < p; k++)
                for(int x = 0; x <= 9; x++)  //下一位
                    f[i][j][k] += f[i - 1][x][mod(k-j, p)];
}

int dp(int n){
    if(!n) return 1;  // 0 % N == 0 也是一种方案
    
    vector<int> nums;
    while(n) nums.push_back(n % 10), n /=10;
    
    int res = 0;
    int last = 0; //前面所有数字之和
    
    for(int i = nums.size() - 1; i >= 0; i--){
        int x = nums[i];
        for(int j = 0; j < x; j++)
            res += f[i + 1][j][mod(-1 * last, p)]; //左分支 填0 ~ x-1
        
        last += x; //右分支
        
        if(!i && last % p == 0) res ++; //最后一个右分支
    }
    
    return res;
}

int main(){
    int l, r;
    while(cin >> l >> r >> p){
        init();
        cout << dp(r) - dp(l - 1) << endl;
    }
    return 0;
}
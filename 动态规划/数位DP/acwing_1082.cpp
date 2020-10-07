/*
* @Description: 1082. 数字游戏
* @Author: Xiaobin Ren
* @Date:   2020-10-05 17:07:52
* @Last Modified time: 2020-10-07 11:55:54
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

//前缀思想 f[r] - f[l-1]
//f[i][j] 表示 最高位是j 一共有i位数的不降数的集合

const int N = 15;
int f[N][N];

void init(){
    for(int i = 0; i <= 9; i++) f[1][i] = 1;  //只有一位的情况下 全部都是1
    
    for(int i = 2; i < N; i++) // 0 ~N 所有的数字 从2位数开始枚举
        for(int j = 0; j <= 9; j++)  // 最高位的数字
            for(int k = j; k <= 9; k++)
                f[i][j] += f[i - 1][k];
}

int dp(int n){
    if(!n) return 1; // 0特判一下 因为0不会出现在nums数组中 
    vector<int> nums;
    while(n) nums.push_back(n % 10), n/=10;
    
    int res = 0; // 答案
    int last = 0;  // 上一位的值 
    for(int i = nums.size() - 1; i>= 0; i--){
        int x = nums[i];
        for(int j = last; j <x; j++){ //左分支 枚举到 x - 1 
            res += f[i+1][j]; //包括当前的第i位，一共还有i + 1位
        }
        if(x < last) break; 
        last = x;
        
        if(!i) res ++; //最后一个分支 没有被break 就是合法的 加上一个
    }
    
    return res;
}

int main(){
    init();
    int l ,r;
    while(cin >> l >> r) cout << dp(r) - dp(l - 1) << endl;
    
    return 0;
}
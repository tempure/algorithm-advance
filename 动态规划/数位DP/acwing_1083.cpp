/*
* @Description: 1083. Windy数
* @Author: Xiaobin Ren
* @Date:   2020-10-07 12:00:43
* @Last Modified time: 2020-10-07 12:01:04
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 15;
int f[N][N];  //f[i][j] 最高位是j 一共有i位数的方案

void init(){
    for(int i = 0; i <= 9; i++) f[1][i] = 1; // 一位数 的情况，0自身不算前导零
    
    for(int i = 2; i < N; i++)  //区间端点
        for(int j = 0; j <= 9; j++) //最高位
            for(int k = 0; k <= 9; k++)
                if(abs(j - k) >= 2) 
                    f[i][j] += f[i - 1][k];
}

int dp(int n){
    if(!n) return 0; //0不算
    
    vector<int> nums;
    while(n) nums.push_back(n % 10), n /=10;
    
    int res = 0;
    int last = -3; //上一位 初始只需要和0-9中每个都差大于2即可
    
    for(int i = nums.size() - 1; i>= 0; i--){
        int x = nums[i];
        for(int j = (i == nums.size()-1); j < x; j++) //左分支 枚举到 x - 1
            if(abs(j - last) >= 2) 
                res += f[i+1][j];
                
        if(abs(x - last) >= 2) last = x;
        else break;
        
        if(!i) res ++;
    }
    
    //处理有前导0的数
    for(int i = 1; i < nums.size(); i++) //位数
        for(int j = 1; j <= 9; j++)
            res += f[i][j];
            
    return res;
}

int main(){
    
    init();
    int l, r;
    cin >> l >> r;
    cout << dp(r) - dp(l - 1) << endl;
    
    return 0;
}
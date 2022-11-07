/*
* @Description: 1085. 不要62
* @Author: Xiaobin Ren
* @Date:   2020-10-07 16:31:24
* @Last Modified time: 2020-10-07 16:31:37
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 10;
int f[N][N];  //最高位是j 有i位 f[i][j]

void init(){
    memset(f, 0, sizeof f);
    for(int i = 0 ; i<= 9 ;i++) f[1][i] = (i != 4);
    
    for(int i = 2; i < N; i++) //位数
        for(int j = 0; j <= 9; j++){
            if(j == 4) continue;
            for(int k = 0; k <= 9; k++){  //枚举2位j k 然后判断
                if(k == 4 || j == 6 && k == 2) continue;
                f[i][j] += f[i - 1][k]; 
            }
        }
}

int dp(int n){
    if(!n) return 1;  //0 满足要求
    
    vector<int> nums;
    while(n) nums.push_back(n % 10), n/=10;
    
    int res = 0;
    int last = 0;  // 储存上一位数字
    
    for(int i = nums.size() - 1; i >= 0; i--){
        int x = nums[i];
        for(int j = 0; j < x; j++){ //左分支
            if(j == 4 || last == 6 && j == 2) continue;
            res += f[i + 1][j];
        }

        if(x == 4 || last == 6 && x == 2) break;
        last = x;
        if(!i) res ++;
    }
    
    return res;
}

int main(){
    init();
    int l, r;
    while(cin >> l >> r && (l  || r))
        cout << dp(r) - dp(l - 1) << endl;
        
    return 0;
}
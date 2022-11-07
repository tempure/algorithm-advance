/*
* @Description: 1081. 度的数量
* @Author: Xiaobin Ren
* @Date:   2020-10-05 15:16:15
* @Last Modified time: 2020-10-05 15:16:26
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 40;  //二进制的位数 31位
int f[N][N];  //f[a][b]从a个数中选b个的方案数
int k, b;

void init(){// 预处理组合数
    for(int i = 0; i < N; i++) //i个里面选j个
        for(int j = 0; j <= i; j++)
            if(!j) f[i][j] = 1;
            else f[i][j] = f[i-1][j] + f[i-1][j-1];
}

int dp(int n){ // 0 ~ n 满足条件的个数
    if(!n) return 0;
    vector<int> nums;
    while(n) nums.push_back(n % b), n /= b;  //储存b进制下的每一位
    
    int res = 0;
    int last = 0;  //前缀有多少个1已i经
    for(int i = nums.size() - 1; i >= 0; i--){ //反着存的 所以要逆着来
        int x = nums[i];
        if(x){  //左分支 
            res += f[i][k-last];  //当前位是0 就要从后边的选出k-last个1
            if(x > 1){
                if(k - last - 1 >= 0) res += f[i][k - last - 1];
                break; //只能填b进制下的0和1 直接break
            }
            else{ 
                last ++; //x==1
                if(last > k) break;
            }
        }
        if(!i && last == k) res++; //最右侧分支的方案
    }
    return res;
}

int main(){

    init();
    int l ,r; //区间
    cin >> l >> r >> k >> b;
    cout << dp(r) - dp(l - 1) << endl; //前缀的思想
    return 0;
}


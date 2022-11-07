/*
* @Description: 482. 合唱队形
* @Author: Xiaobin Ren
* @Date:   2020-09-21 13:07:00
* @Last Modified time: 2020-09-21 13:07:09
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1010;
int a[N], f[N];
int n;
int rf[N];

//双向LIS 和上一题的 登山 一样

int main(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    
    int res = 0;
    
    for(int i = 0; i < n; i++){
        f[i] = 1;
        for(int j = 0; j < i; j++)
            if(a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
    }
    
    for(int i = n - 1; i >=0; i--){
        rf[i] = 1;
        for(int j = n - 1; j > i; j--)
            if(a[j] < a[i]) rf[i] = max(rf[i], rf[j] + 1);
    }
    
    for(int i = 0; i < n; i++)
        res = max(res, f[i] + rf[i] - 1);  //此处减去1 是把f[i] rf[i] 重复了
        
    cout << n - res << endl;
    
    return 0;
}
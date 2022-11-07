/*
* @Description: 1014. 登山
* @Author: Xiaobin Ren
* @Date:   2020-09-21 13:00:48
* @Last Modified time: 2020-09-21 13:03:43
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1010;
int a[N], f[N];
int n;
int rf[N];

// 思路：这个题意有点费解 意思就是先从数组的左端开始走到山顶
//然后又走到山脚 也就是一直走到数组结束
//所以就是双向的LIS 就是求一个单峰LIS的最长 


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
        
    cout << res << endl;
    
    return 0;
}
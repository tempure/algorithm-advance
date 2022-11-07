/*
* @Description: 1010. 拦截导弹
* @Author: Xiaobin Ren
* @Date:   2020-09-21 16:40:55
* @Last Modified time: 2020-09-21 16:41:05
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1010;
int f[N];
int rf[N];
vector<int> a;
/*
dilworth定理：
    “能覆盖整个序列的最少的不上升子序列的个数”等价于“该序列的最长上升子序列长度”
    同理即有：
    “能覆盖整个序列的最少的不下降子序列的个数”等价于“该序列的最长下降子序列长度”
*/
int main(){
    int x;
    while(cin >> x){
        a.push_back(x);
    }
    
    for(int i = a.size() - 1; i >= 0; i--){
        f[i] = 1;
        for(int j = a.size() - 1; j > i; j--)
            if(a[j] <= a[i]) f[i] = max(f[i], f[j] + 1);  //注意相等也可以拦截
    }
    
    int res1 = 0;
    for(int i= 0;i < a.size(); i++) res1 = max(res1, f[i]);
    
    int res2 = 0;
    
    for(int i = 0; i < a.size(); i++){
        rf[i] = 1;
        for(int j =0; j < i; j++)
            if(a[j] < a[i]) rf[i] = max(rf[i], rf[j] + 1);
            
    }
    
    for(int i = 0; i < a.size(); i++) res2 = max(res2, rf[i]);
    
    cout << res1 << endl;
    cout << res2 << endl;
    
    return 0;
    
}

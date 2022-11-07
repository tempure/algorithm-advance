/*
* @Description: 1017. 怪盗基德的滑翔翼  
* @Author: Xiaobin Ren
* @Date:   2020-09-20 21:29:33
* @Last Modified time: 2020-09-20 22:36:02
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 110;
int k;
int a[N];
int f[N];

int main(){
    cin >> k;
    while(k --){
        memset(a, 0, sizeof a);
        memset(f, 0, sizeof f);
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++) cin >> a[i];
        
        for(int i = 1; i <= n; i++){
            f[i] = 1;
            for(int j = 1; j < i; j++)
                if(a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
        }
        
        int res = 0;
        for(int i = 1; i <= n; i++) res = max(res, f[i]);
        
        //由于可以逆向进行 所以直接逆序过来再求一次LIS即可
        reverse(a + 1, a + n + 1);
        
         for(int i = 1; i <= n; i++){
            f[i] = 1;
            for(int j = 1; j < i; j++)
                if(a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
        }
        
        
        for(int i = 1; i <= n; i++) res = max(res, f[i]);
        
        cout  << res << endl;
    }
    
    
    return 0;

}
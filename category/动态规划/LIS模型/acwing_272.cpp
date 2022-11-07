/*
* @Description: 
* @Author: Xiaobin Ren
* @Date:   2020-09-22 11:17:00
* @Last Modified time: 2020-09-22 13:07:26
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3010;
int a[N], b[N];
int n;
int f[N][N];
// n ^ 3 会TLE
/*
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++){
            f[i][j] = f[i - 1][j];
            if(a[i] == b[j]){
                f[i][j] = max(f[i][j], 1);
                for(int k = 1; k < j; k++)
                    if(b[k] < b[j])
                        f[i][j] = max(f[i][j], f[i][k] + 1);
            }
        }
        
    int res = 0;
    for(int i = 1; i <= n; i++) res = max(res, f[n][i]);
    
    cout << res << endl;
    
    return 0;
}
*/
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    
    for(int i = 1; i <= n; i++){
        int maxv = 1; // 1 ~ j - 1 中 f[i - 1][k] + 1 的最大值
        for(int j = 1; j <= n; j++){
            f[i][j] = f[i - 1][j]; //a[i] != b[j] 
           
            if(a[i] == b[j]) f[i][j] = max(f[i][j] ,maxv);
            if(b[j] < a[i]) maxv = max(maxv, f[i][j] + 1);
        }
    }    
    int res = 0;
    for(int i = 1; i <= n; i++) res = max(res, f[n][i]);
    
    cout << res << endl;
    
    return 0;
}

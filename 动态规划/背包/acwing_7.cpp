/*
* @Description: 
* @Author: Xiaobin Ren
* @Date:   2020-09-26 18:28:17
* @Last Modified time: 2020-09-26 18:28:27
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;
int n, m;
int f[N];

//注意没有分组背包 只有其余3种背包混合

int main(){
    
    scanf("%d%d", & n, & m);
    for(int i = 0; i <n; i++){
        int v, w, s;
        scanf("%d%d%d", &v, &w, &s);
        if(s == 0){  //完全背包
            for(int j = v; j <= m; j++) f[j] = max(f[j], f[j - v] + w);
        }
        else
        {
            if(s == -1) s = 1; //01背包是多重背包的特殊情况 直接合并一起写
            for(int k = 1; k <= s; k *= 2){ //二进制优化 把si次 等价于si个同样的物品 然后01背包 每次倍增 
                for(int j = m; j >= k *v; j--)
                    f[j] = max(f[j], f[j - k * v] + k * w);
                s -= k;
            }
            if(s){ //二进制打包之后 剩余的物品 收尾
                for(int j = m; j >= s * v; j --)
                    f[j] = max(f[j], f[j - s * v] + s * w);
            }
        }
    }
    
    cout << f[m] << endl;
    
    return 0;
}
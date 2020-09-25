/*
* @Description: 487. 金明的预算方案
* @Author: Xiaobin Ren
* @Date:   2020-09-25 23:59:38
* @Last Modified time: 2020-09-25 23:59:55
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define v first
#define w second
using namespace std;

typedef pair<int, int> pii;

const int N = 70, M = 32010; //N 物品数 M钱数

int n, m;
pii master[N];
vector<pii> servent[N];
int f[M];

int main(){
    cin >> m >> n;
    for(int i = 1; i <= n; i++){
        int v, w, q;
        cin >> v >> w >> q;  //v价格 w重要程度 q主还是附
        if(!q) master[i] = {v, v * w};
        else servent[q].push_back({v, v * w});  //加入附件
    }
    
    for(int i = 1; i <= n; i++)
        if(master[i].v){
            for(int j = m; j >= 0; j--)
                for(int k = 0; k < 1 <<  servent[i].size(); k++){
                    int v = master[i].v, w = master[i].w;
                    for(int u = 0; u < servent[i].size(); u++)
                        if(k >> u & 1){
                            v += servent[i][u].v;
                            w += servent[i][u].w;
                        }
                        if(j >= v) f[j] = max(f[j], f[j - v] +w);
                }
        }
    
    cout << f[m] << endl;
    
    return 0;
}

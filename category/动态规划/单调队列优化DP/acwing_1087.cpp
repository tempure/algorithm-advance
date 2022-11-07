/*
* @Description: 1087. 修剪草坪
* @Author: Xiaobin Ren
* @Date:   2020-10-11 19:29:30
* @Last Modified time: 2020-10-11 19:29:40
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int N = 100010;
ll s[N];  //前缀和
ll f[N];
int q[N];
int n, m;

ll g(int i){
    return  f[i-1] - s[i];
}

int main(){
    cin >> n >> m;
    
    for(int i = 1; i <=n; i++){
        cin >> s[i];
        s[i] += s[i-1];
    }
    
    int hh = 0, tt = 0;
    for(int i = 1; i <= n;i ++){
        if(q[hh] <i- m) hh ++;
        f[i] = max(f[i-1], g(q[hh]) + s[i]);
        while(hh <= tt && g(q[tt]) < g(i)) tt--;
        q[++tt] = i;
    }
    
    cout << f[n] << endl;
    
    return 0;
}
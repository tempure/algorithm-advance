/*
* @Description: 1088. 旅行问题
* @Author: Xiaobin Ren
* @Date:   2020-10-09 00:14:32
* @Last Modified time: 2020-10-09 00:14:41
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

//环形DP 将数组复制2次拼接
//每个位置 的值 是当前的油量减去能走的路程
//如果所有起点开始长度为n的前缀的前缀和 都大于0 那么就可以走到
//前缀和s[r] - s[l-1] l-1是开头固定的，那么只需要找到最小的r如果都大于0 那么可以 问题转换为滑动窗口
//顺时针 逆时针都做一次 有一个方向可以 就算可以

const int N = 2e6 + 10;  //开2倍长度 拼接
int n;
int p[N], d[N];
ll s[N];
int q[N];  //队头下标
bool ans[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i] >> d[i];
    
    //顺时针做一次 注意：顺时针是pi - di 逆时针就是pi - d[i-1] 因为放置的顺序是逆时针的 但是走的的顺序可以顺可以逆
    for(int i = 1; i <= n; i++) s[i] = s[i+n] = p[i] - d[i];
    for(int i = 1; i <= n * 2; i++) s[i] += s[i-1];  //前缀和
    
    int hh = 0, tt = -1;
    for(int i = n * 2; i; i--){
        if(hh <= tt && q[hh] >= i + n) hh++;
        while(hh <= tt && s[q[tt]] >= s[i]) tt--;
        q[++tt] = i;
        if(i <= n){
            if(s[q[hh]] >= s[i-1]) ans[i] = true;
        }

    }
    
    //逆时针
    d[0] = d[n];
    // memset(q,0,sizeof q);
    for(int i = 1; i <= n; i++) s[i] = s[i + n] = p[i] - d[i-1];
    for(int i = 1; i <= n * 2; i++) s[i] += s[i-1];
    
    hh = 0, tt = -1;
    for(int i = 1; i <= n * 2; i++){
        if(hh <= tt && q[hh] < i - n) hh++;
        if(i > n){
            if(s[q[hh]] <= s[i]) ans[i-n] = true;
        }
         while(hh <= tt && s[q[tt]] <= s[i]) tt--;
        q[++tt] = i;
    }
    
    for(int i = 1; i <= n; i++)
        if(ans[i]) puts("TAK");
        else puts("NIE");
        
    return 0;
}
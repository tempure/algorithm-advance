/*
* @Description: 180. 排书
* @Author: Xiaobin Ren
* @Date:   2020-10-22 00:09:25
* @Last Modified time: 2020-10-22 00:09:35
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//IDA* 就是迭代加深 + 估价函数
//后继关系:n和n + 1 互为后继
//将任意一段改变位置，整个当前的序列后继关系 将被改变3个
//假设所有的错误的后继关系有tot个 估价函数就是tot / 3 上取整 也就是(tot + 2) / 3 下取整
//一个升序的序列 tot就是0 那么估价函数的值就是0

const int N = 15;
int n;
int q[N];
int w[5][N];

int f(){
    int tot = 0;
    for(int i = 0; i +1 < n; i++)
        if(q[i + 1] != q[i] +1)
            tot ++;
            
    return (tot + 2) / 3;
}

bool dfs(int depth, int max_depth){
    if(depth + f() >  max_depth) return false;
    if(f() == 0) return true;
    
    for(int len = 1; len <= n; len++) //区间长度
        for(int l = 0; l + len - 1 < n; l++){  //枚举区间起点
            int r = l + len - 1;
            for(int k = r + 1; k < n; k++){ //将当前区间放到k位置的后面,枚举k从r + 1开始
                //备份状态
                memcpy(w[depth], q, sizeof q);
                int y = l;
                
                for(int x = r + 1; x <= k; x ++, y ++) q[y] = w[depth][x];
                for(int x = l; x <= r; x ++, y ++) q[y] = w[depth][x];
                
                if(dfs(depth + 1, max_depth)) return true;
                //还原备份
                memcpy(q, w[depth], sizeof q); 
            }
        }
    return false;
}

int main(){
    int t; cin >> t;
    while(t --){
        cin >> n;
        for(int i=0; i < n; i++) cin >> q[i];
        
        int depth = 0;
        while(depth < 5 && !dfs(0, depth)) depth ++;
        
        if(depth >= 5) cout << "5 or more" << endl;
        else cout << depth << endl;
    }
    return 0;
}
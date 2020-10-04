/*
* @Description: 1075. 数字转换
* @Author: Xiaobin Ren
* @Date:   2020-10-04 12:45:06
* @Last Modified time: 2020-10-04 12:45:16
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;


//注意是变换步数 不是数的个数

//对于1~n每个数，把他的约数之和 和和其连一条无向边，然后就是树的直径问题 边权都是1
//试除法 sqrt(n) 复杂度能过 n * sqrt(n) 但是可以优化 用筛法
//从2~n枚举 然后筛掉每个数的倍数 复杂度n * ln(n)

const int N = 50010;
int n, h[N], ne[N], e[N], idx;
int sum[N];  //每个数的约数之和
bool st[N];
int ans;

void add(int a, int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

int dfs(int u){
    int d1 = 0, d2 = 0; //最大子节点长度和次大子节点长度
    for(int i = h[u]; i != -1 ; i = ne[i]){
        int j = e[i];
        int d = dfs(j) + 1;
        if(d >= d1) d2 = d1, d1 = d;
        else if(d > d2) d2 = d;
    }
    ans = max(ans, d1 + d2);
    
    return d1;
}
int main(){
     
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 2; j <= n/i; j++) // i * j <=n 防止溢出 写为除法 j是倍数
            sum[i * j] += i;
            
    memset(h, -1 ,sizeof h);
    
    for(int i = 2; i <= n; i++)
    // 约数要小于自身 1的约数之和是0 但是题目要求正整数 所以从2开始
    //如果从1开始，那么1和0之间会有一条边，但是为什么这样输出的结果就是0？
        if(i > sum[i]){
            add(sum[i], i);
            st[i] = true;
        }
        
    //可能有多棵树 从所有没有遍历的点 为根 来一次dfs 就遍历了整个森林
    for(int i = 1; i <= n; i++)
        if(!st[i]) dfs(i);
    
    cout << ans << endl;
    
    return 0;
}
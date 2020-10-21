/*
* @Description: 170. 加成序列
* @Author: Xiaobin Ren
* @Date:   2020-10-21 18:49:12
* @Last Modified time: 2020-10-21 18:49:21
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 110;
int path[N];

int n;
//从大到小枚举下一个数 可以减少长度
//排除冗余：如果已经有2个数等于某个数 就不用尝试其它的数

bool dfs(int u, int max_depth){  //当前层数 最大层数
    if(u > max_depth)return false;
    if(path[u - 1] == n) return true; //u-1是因为必须搜索完上一层，这一层开始才能判断是否符合
    bool st[N] = {0};
    for(int i = u -1; i >= 0; i--) //枚举2个数的和
        for(int j = i; j >= 0; j--){
            int s = path[i] + path[j];
            // s <= path[u-1]  因为要保持序列的严格递增
            if(s > n || s <= path[u - 1] || st[s]) continue;
            
            st[s] = true;
            path[u] = s;
            if(dfs(u + 1, max_depth)) return true;
        }
        return false;
}

int main(){
    while(~scanf("%d", &n)&& n){
        path[0] = 1;
        int depth = 1;
        while(!dfs(1, depth)) depth++;
        for(int i = 0; i < depth; i++) cout << path[i] << ' ';
        cout << endl;
    }
    return 0;
}
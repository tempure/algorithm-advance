/*
* @Description: 1106. 山峰和山谷
* @Author: Xiaobin Ren
* @Date:   2020-10-14 15:32:54
* @Last Modified time: 2020-10-14 15:33:20
*/
#include <iostream>
#include<algorithm>
#include <cstring>
using namespace std;
#define x first
#define y second

const int N = 1010, M = N * N;
typedef pair<int, int> pii;
int n;
int h[N][N];
pii q[M];
bool st[N][N];

//注意是高度相同 的连通块 再进行周围的判断 一个连通块的元素肯定都是一样的
//一个连通块周围所有元素 都比连通块高 那就是山谷 反之就是山峰
//bfs函数调用一次就会遍历一整个连通块

void bfs(int sx, int sy, bool & has_heigher, bool & has_lower){
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = true;
    
    while(hh <= tt){
        pii t = q[hh++];
        for(int i = t.x - 1; i <= t.x + 1; i++)
            for(int j = t.y - 1; j <= t.y + 1; j++){
                if(i < 0 || i >= n || j <0 || j >= n) continue;
                //只要周围的点高度和中心点不一样，那就不在同一个连通块里 需要
                //高度相同的 就直接不会进入下面的if判断 
                if(h[i][j] != h[t.x][t.y]){
                    if(h[i][j] > h[t.x][t.y]) has_heigher = 1;
                    else has_lower = 1;
                }
                else if(!st[i][j]){
                    q[++tt] = {i,j};
                    st[i][j] = 1;
                }
            }
    }
}

int main(){
    scanf("%d", &n);
    
    for(int i = 0 ; i<n; i++)
        for(int j = 0 ; j  < n; j++)
            scanf("%d" ,&h[i][j]);
            
    int peak = 0, valley = 0;
    for(int i = 0; i < n; i++)  
        for(int j = 0 ; j < n; j++)
            if(!st[i][j]){
                bool has_heigher = false, has_lower = false;
                bfs(i ,j, has_heigher, has_lower);
                //遍历整个连通块之后 周围没有比当前连通块高的就是山峰
                //反之是山谷 或者是一整个连通块 那就都算 都+1
                if(!has_heigher) peak++;
                if(!has_lower) valley ++;  //不用else  不是二选一 可能
            }
    printf("%d %d\n", peak, valley);
    
    return 0;
}
/*
* @Description: 1126. 最小花费
* @Author: Xiaobin Ren
* @Date:   2020-10-23 10:13:51
* @Last Modified time: 2020-10-23 10:17:36
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

//求乘积最大的路径 边权为(1 - 税率)
//取log就变成了相加 求最长路径
//税率都小于1 所以log的值都是负的 又因为log函数单调递增
//所以求负数和的最大值，取反后，就是求正数的最小值 可用dijkstra/spfa
//注意：如果没有边权没有0<w<1 这个方法就不能用
//以上分析说明了，这个问题可以等价转换为单源最短路问题，所以可以直接把dijkstra的加改为乘 然后求最大

//直观上的理解：每次dijkstra都会找出最大的点来更新其他的点，保持最优 所以可以找到最大的

const int N = 2010;
int n, m, S, T;
double g[N][N]; //0表示没有边相连
double dist[N];
bool st[N];

void dijkstra(){
    dist[S] = 1;
    for(int i = 1; i <= n;i++){
        int t = -1;
        for(int j = 1; j <=n; j++)
            if(!st[j] && (t == -1 || dist[t] < dist[j]))
                t = j;
        st[t] = true;
        
        for(int j = 1; j <= n; j++)
            dist[j] = max(dist[j], dist[t] * g[t][j]);
    }
}


int main(){
    scanf("%d%d", &n, &m);
    
    
    while(m --){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        double z = (100.0 - c) / 100.0;
        g[a][b] = g[b][a] = max(g[a][b], z); //存储较大边
    }
    
    scanf("%d%d", &S, &T);
    
    dijkstra();
    
    printf("%.8lf\n", 100.0 / dist[T]);
    return 0;
}
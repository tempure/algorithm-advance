/*
* @Description: 1100. 抓住那头牛
* @Author: Xiaobin Ren
* @Date:   2020-10-14 23:34:15
* @Last Modified time: 2020-10-14 23:34:25
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 2e5 + 10;

int n, k;
int q[N];
int dist[N];

//注意n和k的大小关系是不确定的

int bfs(){
    memset(dist, -1 ,sizeof dist);
    dist[n] = 0;
    q[0] = n;
    //相当于每次转移一层，每层都进行三种走法的尝试
    //最先到达k的走法 则是最树的最短路
    int hh = 0, tt = 0;
    while(hh <= tt){
        int t = q[hh++];
        if(t == k) return dist[k];
        if(t + 1 < N && dist[t + 1] == -1){
            dist[t + 1] = dist[t] + 1;
            q[++tt] = t + 1;
        } 
        if(t - 1 >= 0 && dist[t-1] == -1){
            dist[t-1] = dist[t] + 1;
            q[++tt] = t - 1;
        }
        if(t * 2 < N && dist[t * 2] == -1){
            dist[t * 2] = dist[t] + 1;
            q[++tt] = t * 2;
        }
    }
    
    return -1;
}

int main(){
    cin >> n >> k;
    cout << bfs() << endl;
    return 0;
}
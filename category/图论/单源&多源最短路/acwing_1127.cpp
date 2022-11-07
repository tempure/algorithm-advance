/*
* @Description: 1127. 香甜的黄油
* @Author: Xiaobin Ren
* @Date:   2020-10-22 22:19:27
* @Last Modified time: 2020-10-22 22:21:20
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

//枚举所有点为起点，求所有最短路的路径和
//本质是多源最短路，但是floyd会超时
//堆优化dijkstra 每个点都求一次 
//spfa 复杂度O(m) 更快 每个点求一次 如果被卡掉的话 就不能用了 退化为O(n * m)

const int N = 810, M = 3000;
int n, p, m;
const int INF = 0x3f3f3f3f;
int id[N];
int h[N], ne[M], e[M], idx, w[M];
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

int spfa(int start){
	//初始化要注意 dist的初始化 放在spfa函数里面 如果要多次调用spfa的话
    memset(dist, 0x3f, sizeof dist);    
    memset(st, 0, sizeof st);
    
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    st[start] = 1;
    
    while(q.size()){
        int t = q.front(); q.pop();
        st[t] = 0;
        
        for(int i = h[t]; ~i; i = ne[i]){
            int j = e[i];
            if(dist[j] > dist[t] + w[i]){
                dist[j] = dist[t] + w[i];
                if(!st[j]){
                    q.push(j), st[j] = 1;
                }
            }
        }
    }
    
    int res = 0;
    for(int i = 0; i < n; i++){
        int j = id[i];
        //枚举所有奶牛所在的牧场，如果dist是INF，说明不可达 就返回INF
        if(dist[j] == INF) return INF;
        res += dist[j];
    }
    
    return res;
}

int main(){
    cin  >> n >> p >> m;
    for(int i = 0; i < n; i++) cin >> id[i];
    memset(h, -1, sizeof h);

    
    for(int i =0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c); add(b, a, c);
    }
    
    int res = INF;
    //spfa返回所有奶牛到当前为起点的牧场的距离之和
    for(int i = 1; i <= p; i++) res = min(res, spfa(i));
    
    cout << res << endl;
    
    return 0;
}
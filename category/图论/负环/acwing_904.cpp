#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

//常用2种spfa求负环的方法，常用的是第二种
//统计每个点入队的次数 如果某个点入队n次 那么存在负环
//统计当前每个点的最短路中所包含的边数 如果某个点的 最短路包含的边数>=n 那么有能说明存在负环

//注意虫洞是单向边

const int N = 510, M = 5500;

int n, m1, m2; //m1 双向边和单向边的数量
int h[N], ne[M], w[M],  e[M], idx;
int dist[N];
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

bool spfa(){
    int hh = 0, tt = 0;
    memset(dist, 0, sizeof dist); //注意在求负环中  由于虚拟原点的思路 每个点和原点的距离 都初始化为0
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);

    for(int i = 1; i <= n; i++){
        q[tt++] = i;
        st[i] = true; //所有点都全部入队
    }
    while(hh != tt){
        int t = q[hh++];
        if(hh==N) hh = 0;
        st[t] = false; //不在队列里面就是false

        for(int i = h[t]; i!= -1; i = ne[i]){
            int j =e[i];
            if(dist[j] > dist[t] + w[i]){
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] +  1;
                if(cnt[j] >= n) return true;
                if(!st[j]){
                    q[tt++] = j;
                    if(tt == N)  tt= 0;
                    st[j] = true;
                }
            }
        }
    }
    return false; //不存在负环
}

int main(){
    int t;
    cin >> t;
    while(t --){
        cin >> n >> m1 >> m2;
        memset(h, -1, sizeof h);
        idx = 0;

        while(m1 --){
            int a, b, c;
            cin >> a >> b >> c;
            add(a, b ,c), add(b, a, c);
        }
        while(m2 --){
            int a, b, c;
            cin >> a >> b >> c;
            add(a, b, -c);  //注意是负边
        }
        if(spfa()) puts("YES");
        else puts("NO");
    }

    return 0;
}
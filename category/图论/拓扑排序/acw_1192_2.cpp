#include <bits/stdc++.h>
using namespace std;

/*
有向图，所有边权都大于0，判断是否存在环
直接拓扑排序即可，因为环上的点都不会入队，因为完全不符合--d[x]==0的条件

总结：

//如果边权有负有正 那么spfa判负环或正环
//如果边权>=0 强连通分量 判断正环 如果一个SCC中存在正边说明存在正环
//如果边权全部>0 拓扑排序即可 判断队列元素个数是否 == n - 1
*/

const int N = 10010, M = 20010;
int n,m;
int h[N], e[M], ne[M], idx;
int q[N];
int dist[N];
int d[N];

void add(int a, int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

bool topsort(){
   int hh = 0, tt = -1;
   for(int i = 1; i<= n; i++)
    if(!d[i]) 
        q[++tt] = i;

    while(hh <= tt){
        int t = q[hh++];
        for(int i= h[t]; ~i; i = ne[i]){
            int j= e[i];
            if(-- d[j] == 0) q[++tt] = j;
        }
    }
    return tt == n - 1; //0~n - 1 一共n个元素
}

void solve(){
    cin >> n >> m;
    memset(h, -1, sizeof h); 
    while(m --){
        int a,b;
        cin >> a >> b;
        add(b, a);
        d[a]++;
    }
    if(!topsort()) puts("Poor Xed");
    else{ 
        for(int i =1; i <= n; i++) 
            dist[i] = 100;
        for(int i=  0; i< n; i++){
            int j = q[i];
            for(int k = h[j]; ~k; k = ne[k])
                dist[e[k]] = max(dist[e[k]], dist[j] + 1);
        }
        int res = 0;
        for(int i= 1; i <= n; i++) 
            res += dist[i];
        cout << res << endl;
    }
}

int main(){
    solve();
    return 0;
}
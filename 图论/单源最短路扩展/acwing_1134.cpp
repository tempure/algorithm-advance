#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//先求出到每个点的最短路的值 然后分别求出有多少路径
//这种求最短路条数的题，肯定不会存在权值和为0的环或者负环，因为这样多转一圈就是一个新的路径
//即有无数条 路径，但是本题都是无向无权图 边权全部为1
//最短路树 也就是拓扑图 记录每个点的 前驱 
//最短路的求解过程 需要满足拓扑序 只有dijkstra/bfs满足入队出队一次就是最优 拓扑序的遍历
//spfa实际上也可以，如果有负权的话 

const int N = 100010, M = 400010;
const int mod = 100003;

int n, m;
int h[N], e[M], ne[M], idx;
int dist[N], cnt[N];
int q[N];

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void bfs(){
	memset(dist, 0x3f, sizeof dist);
	dist[1] = 0;
	cnt[1] = 1; //原点到自己的初始最短路就是1
	int hh = 0, tt = 0;
	q[0] = 1;

	while(hh <= tt){
		int t = q[hh++];
		for(int i = h[t]; i != -1; i = ne[i]){
			int j = e[i];
			if(dist[j] > dist[t] + 1){ //更新最短路 同时更新 cnt
				dist[j] = dist[t] + 1;
				cnt[j] =  cnt[t];
				q[++tt] =  j;	
			}
			else if(dist[j] == dist[t] + 1){ //距离相同 就加上
				cnt[j] = (cnt[j] + cnt[t]) % mod;
			}
		}
	}
}

int main(){
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    while(m --){
    	int a, b;
    	scanf("%d%d", &a, &b);
    	add(a, b); add(b, a);
    }
    bfs();
    
    for(int i =1; i <=n; i++) printf("%d\n", cnt[i]);
    
    return 0;
}
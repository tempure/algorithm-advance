#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
#define x first
#define y second

/*
航线单向无环有负边 道路双向无负权边
spfa会被卡掉
没有负权的边的集合看成团 有负权的边 看成连接团的拓扑序的边
每个团内部dijkstra  团之间 使用拓扑序 因为负权边都是有向无环的
可以dfs/bfs/并查集处理连通块 也就是团 每个连通块内的点都有块的id
*/

/* 
1.先输入所有双向道路，然后DFS出所有连通块，计算两个数组: 
id[]存储每个点属于哪个连通块;vector<int> block[]存储每个连通块里有哪些点;
2.输入所有航线，同时统计出每个连通块的入度。
3.按照拓扑序依次处理每个连通块。
4.每次从队头取出一个连通块的编号bid
5.将该block[bid]中的所有点加入堆中，然后对堆中所有点做dijkstra算法。
6.每次取出堆中距离最小的点ver。
7.然后遍历ver的所有邻点j。如果id[ver] == id[i]，那么如果j能被更新，
则将j插入堆中;如果id[ver] != id[i]，则将id[i]这个连通块的入度减1，
如果减成0了，则将其插入拓扑排序的队列中。
*/

const int N = 25010, M = 150010;
const int INF = 0x3f3f3f3f;
int n,mr, mp, s;
int h[N], ne[M], e[M], idx, w[M];
int id[N]; 
vector<int> block[N]; //每个连通块里面有哪些点
int dist[N]; 
int bcnt; //连通块 大点 的编号
int din[N]; //每个连通块的入度
bool st[N];
queue<int> q;

void add(int a, int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

void dfs(int u, int bid){  //当前的点 以及当前的点所在块的bid
	id[u] = bid;
	block[bid].push_back(u);

	for(int i = h[u]; ~i; i=ne[i]){
		int j = e[i];
		if(!id[j]) dfs(j, bid);
	}
}

void dijkstra(int bid){
	priority_queue<pii, vector<pii>, greater<pii> > heap;
    memset(st, 0, sizeof st);
    
	for(auto ver:block[bid]) heap.push({dist[ver], ver});

	while(heap.size()){
		auto t = heap.top();
		heap.pop();

		int ver = t.y, distance  = t.x;

		if(st[ver]) continue;
		st[ver] = true;

		for(int i = h[ver]; ~i; i = ne[i]){
			int j = e[i];
			if(dist[j] > dist[ver] + w[i]){
				dist[j] = dist[ver] + w[i];
				if(id[j] == id[ver]) heap.push({dist[j], j});
			}
			//不是该连通块的点 并且入度为0 那就加入队列
			if(id[j] != id[ver] && --din[id[j]] == 0) q.push(id[j]);
		}
	}
}

void topsort(){
	memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    
	for(int i = 1; i <= bcnt; i++)
		if(!din[i]) q.push(i);
		
	while(q.size()){
		int t = q.front();
		q.pop();

		dijkstra(t); //连通块的内部进行dijkstra
	}
}

int main(){
         
    scanf("%d%d%d%d", &n,&mr, &mp, &s);
    memset(h, -1, sizeof h);
    
    while(mr--){
        int a,b,c ;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }

  	for(int i = 1;i <=n;i ++)
  		if(!id[i])
  			dfs(i, ++bcnt);  //处理连通块

  	while(mp --){
  		int a, b, c;
  		scanf("%d%d%d", &a, &b, &c);
  		add(a, b ,c );
  		din[id[b]] ++;
  	}

  	topsort();

  	for(int i = 1; i <= n; i++){
  		if(dist[i] > INF / 2) puts("NO PATH");
  		else printf("%d\n", dist[i]);
  	}
    
    return 0;
}
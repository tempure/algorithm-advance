#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

//次短路径问题 
//先求一边最短路及其路径数量 然后 再求次短路 最后判断 如果长度多1  就加上
//d[i][0] 表示1到i的最短路径 cnt 同理
//d[i][1] 表示1到i的次短路径
//每个点的集合找到最短路和次短路 并且统计次数

const int N = 1010, M = 10010;

struct Ver{
	int ver, type, dist;
	bool operator> (const Ver &W) const{
		return dist > W.dist; // 大根堆 重载大于号
	}
};

int n, m, S, T;
int h[N], e[M], w[M], ne[M], idx;
int dist[N][2];
int cnt[N][2];
bool st[N][2];

void add(int a, int b, int c){
	e[idx] = b;
	ne[idx] = h[a];
	w[idx] = c;
	h[a] =idx ++;
}

int dijkstra(){
	memset(dist, 0x3f, sizeof dist);
	memset(st, 0, sizeof st);
	memset(cnt, 0, sizeof cnt);
	dist[S][0] = 0; cnt[S][0] = 1;

	priority_queue<Ver, vector<Ver>, greater<Ver> > heap;
	heap.push({S, 0, 0});

	while(heap.size()){
		Ver t = heap.top();
		heap.pop();

		int ver = t.ver, type = t.type, distance = t.dist, count = cnt[ver][type];
		if(st[ver][type]) continue;
		st[ver][type] = true;


		for(int i = h[ver]; i != -1; i = ne[i]){
			int j  = e[i];
			if(dist[j][0] > distance + w[i]){
				dist[j][1] = dist[j][0], cnt[j][1] = cnt[j][0]; //最小值沦为次小值
				heap.push({j, 1, dist[j][1]}); //次小值加入堆
				dist[j][0] = distance + w[i], cnt[j][0] = count;
				heap.push({j, 0, dist[j][0]}); //最小值加入堆
			}
			else if(dist[j][0] == distance + w[i]) cnt[j][0] += count;
			else if(dist[j][1] > distance + w[i]){
				//比最小值小 比次小值大 更新次小值
				dist[j][1] = distance + w[i], cnt[j][1] = count;
				heap.push({j, 1, dist[j][1]});
			}
			else if(dist[j][1] == distance + w[i]) cnt[j][1] += count; //等于次小值
		}
	}

	int res = cnt[T][0];
	if(dist[T][0] + 1 == dist[T][1]) res += cnt[T][1];

	return res;
}

int main(){
  	int t; cin >> t;
  	while(t --){
	   	scanf("%d%d", &n ,&m);
	   	memset(h, -1 ,sizeof h);
	   	idx = 0;

	   	while(m --){
	   		int a, b, c;
	   		scanf("%d%d%d", &a, &b,&c);
	   		add(a, b, c);
	   	}

	   	scanf("%d%d", &S, &T);
	   	printf("%d\n", dijkstra());
  	} 

    return 0;
}
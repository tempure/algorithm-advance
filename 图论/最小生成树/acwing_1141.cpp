#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

//在图的每一个连通块内求最小生成树 这个图有多个连通块 只需要保持最初的连接关系即可
//同时满足去掉的边权最大 也就是保留的边权最小 这和最小生成树是等价的
//prim一次只能处理一个连通块 实现代码比较麻烦 用kruskal的本质原理 会自然而然处理非连通图

//kruskal算法在一个非连通图的处理：不会影响连通性，因为每次都会遍历一条“存在的边”
//不存在的边是不会去处理的，所以最后连通块并不会受到影响
//对于连通性的处理：一个最小生成树n个点 则有 n-1条边，如果不连通 那么处理的“次数就会小于n - 1"
//所以可以判断一个图是否存在"最小生成树" 只需要 开个cnt记录一下 每次路径 压缩时候都+1 非连通的边是不会处理的

const int N = 110, M = 210;
int n, k, m;
int p[N];

struct Edge{
	int a, b, w;
	bool  operator< (const Edge & t) const{
		return w < t.w;
	}
}e[M];

int find(int x){
	if(x != p[x]) p[x] = find(p[x]);
	return p[x];
}

int main(){
	cin >> n >>  m;
	for(int i =1; i <= n; i++) p[i] = i;

	for(int i = 0; i < m; i++){
		int a, b ,w;
		cin >> a >> b >> w;
		e[i] = {a, b, w};
	}
	sort(e, e + m);
	int res = 0;
	for(int i = 0; i < m; i++){
		int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
		if(a != b) p[a] = b; //当前ab是最优解 也就是排序后的边 
		else res += w; //已经有边了 那么就去掉 更新答案
	}
	
	cout << res << endl;
	return 0;
}
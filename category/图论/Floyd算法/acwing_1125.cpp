#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

/*
直径定义：一个图中，2点间最短路的最大值 最短路是边权值和 不是欧几里得距离 
本题的题意有些含糊，意思就是在一个有很多连通块的图中 只加上一条边 连接其中某2个连通块
直径:并不是欧几里得距离 而是路径的权值和 样例给的12.07就是2条边的和
不是要加很多边 也不是全连通，一个全连通的图的直径是定值，不会由于内部边的连接改变而改变大小
求出每个连通块中的直径 然后所有的直径 取max
接着开始枚举边来连接连通块 这样一条边可以将2个连通块连接起来
然后就是该边的距离+2个点分别之前求出的连通块的直径的和 
答案要么是一个连通块的直径，或者就是最后连边后的和 然后取max就是直径 也是最小的直径
*/

typedef pair<int, int> pii;
#define x first
#define y second

const int N = 150;
const double INF = 1e20;
int n;
pii q[N];
char g[N][N];
double d[N][N], maxd[N];

double get_dist(pii a, pii  b){
	double dx = a.x - b.x;
	double dy = a.y - b.y;

	return sqrt(dx * dx + dy * dy);
}

int main(){
	cin >> n;
	for(int i =0; i < n; i++) cin >> q[i].x >> q[i].y;
	for(int i = 0; i < n; i++) cin >> g[i];
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j <n; j++)
			if(i !=j) {
				if(g[i][j] == '1') d[i][j] = get_dist(q[i], q[j]);
				else d[i][j] = INF;
			}
	//floyd
	for(int k = 0; k < n; k++)
		for(int i = 0; i< n; i++)
			for(int j = 0; j < n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	
	//每个连通块内 每个点距离最远的点的距离
	//由于距离都是欧几里得直线距离 所以最短路直接就是两点的距离
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(d[i][j] < INF)
				maxd[i] = max(maxd[i], d[i][j]);
	double res1 = 0;
	for(int i = 0; i < n; i++) res1 = max(res1, maxd[i]);

	//不连通边中 枚举任意2个点 然后连边
	double res2 = INF;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(d[i][j] >= INF)
				res2 = min(res2, get_dist(q[i], q[j]) + maxd[i] + maxd[j]);

	printf("%lf\n", max(res1, res2));

	return 0;
}
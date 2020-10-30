//不超过N条边的最短路可以用bellman-ford求出
//恰好N条边 需要floyd 的思想 但是实际上不是floyd
//需要离散化 因为只有100个边 最多也就200个点 如果直接1000个点 会超时
//floyd DP的过程中 d[k][i][j]表示的是从i到j只经过编号为1~k的点 利用这一个性质
//重新定义DP过程为 从i到j 恰好经过k条边的最短路径
//d[a + b, i, j] = min{d[a,i,s] + d[b,s,j]}; s是中间点 也就是第a个点
//每2个点之间到达需要的边数，是互不相干的，独立的，可以用倍增的思想
//求出[1][i][s], [2][i][s] , [4][i][s] 第一维的复杂度就降为log

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <map>  

using namespace std;
const int N = 210;
int n, m, S, E;
int k; //最多k条边
int g[N][N];
int res[N][N]; // 答案 res[i][j] 从i走到j的答案

void mul(int c[][N], int a[][N], int b[][N]){
	static int temp[N][N];
	memset(temp, 0x3f, sizeof temp);
	for(int k =1; k <= n; k++)
		for(int i = 1;  i<=n; i++)
			for(int j = 1; j <= n; j++)
				temp[i][j] = min(temp[i][j],  a[i][k] + b[k][j]);
	memcpy(c, temp, sizeof temp);
}

void qmi(){
	memset(res, 0x3f, sizeof res);
	for(int i =1 ; i<= n; i++) res[i][i] = 0; //经过0条边的答案

	while(k){
		if(k & 1) mul(res, res ,g); // res = res * g
		mul(g, g, g); // g = g *  g
		k >>= 1;
	}
}

int main(){
    cin >> k >> m >> S >> E;    

    memset(g, 0x3f, sizeof g);
    // for(int i = 1; i <= N; i++) g[i][i] = 0; 不能初始化 
    //在类Floyd算法中有严格的边数限制，如果出现了i->j->i的情况其实在i->i中是有2条边的
    //要是初始化g[i][i]=0,那样就没边了，影响了类Floyd算法的边数限制
    map<int, int> ids; //离散化
    if(!ids.count(S)) ids[S] = ++n;
    if(!ids.count(E)) ids[E] = ++n;
    S = ids[S], E = ids[E];
    
    while(m --){
        int a,b,c;
        cin >> c >> a >> b;
        if(!ids.count(a)) ids[a] = ++n;
        if(!ids.count(b)) ids[b] = ++n;
        a = ids[a], b = ids[b];
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    qmi();
    cout << res[S][E] << endl;

    return 0;
}
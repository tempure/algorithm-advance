#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <deque>
using namespace std;
typedef pair<int, int> pii;
#define x first
#define y second

//DP + 状压 + 最短路
//边权是0或者1 最快是双端队列BFS
//用二进制state表示钥匙状态 有i类的钥匙 i位置就是1 否则就是0
//拆点 每个点的状态细分
//拿钥匙的转移边权是0 上下左右走的转移方式 边权是1

const int N = 11, M = N * N, E = 400, P = 1 << 10; 

int n, m, p, k;
int h[M], e[E], ne[E], idx;
int w[E];
int g[N][N], key[M]; //key表示每个格子上有哪些钥匙
int dist[M][P]; //到每个点的每种状态的距离
bool st[M][P];

set<pii> edges;

void add(int a, int b, int c){ //加边函数 特殊 
    e[idx] = b; w[idx] = c, ne[idx] = h[a], h[a] =  idx ++;
}

void build(){
     //建图， 要处理每个点周围的点
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
     for(int i = 1; i <= n;  i++)
        for(int j = 1; j <= m; j++)
            for(int u = 0; u < 4; u++){
                int x = i + dx[u], y = j + dy[u];
                if(!x || x > n || !y || y > m) continue ;//出界
                int a = g[i][j], b = g[x][y];
                if(edges.count({a, b}) == 0) add(a, b, 0); //可以直接通过 不是门 门已经main函数加边的时候就已经处理了
            }
}

int bfs(){
    deque<pii> q;
    memset(dist, 0x3f, sizeof dist);
    dist[1][0] = 0; //起点 没有钥匙 状态二进制全0
    q.push_back({1, 0});
    
    while(q.size()){
        pii t = q.front();
        q.pop_front();
        
        if(st[t.x][t.y]) continue; //已经出队过
        st[t.x][t.y] = true;
        
        if(t.x  == n * m) return dist[t.x][t.y];
        
        if(key[t.x]){
            int state = t.y | key[t.x]; //拿到钥匙之后的状态
            if(dist[t.x][state] > dist[t.x][t.y]){
                dist[t.x][state]= dist[t.x][t.y];
                q.push_front({t.x, state}); //边权是0 就加入队头
            }
        }
        
        for(int i = h[t.x]; i!=-1; i = ne[i]){
            int j =e[i];
            if(w[i] && !(t.y >> w[i] - 1 & 1)) continue;  //有门但是没有钥匙
            //没有门 可以直接过去
            if(dist[j][t.y] > dist[t.x][t.y] + 1){
                dist[j][t.y] = dist[t.x][t.y] + 1;
                q.push_back({j, t.y});
            }
        }
    }
    
    return -1;
}

int main(){
    cin >> n >> m >> p >> k;
    memset(h ,-1, sizeof h);
    for(int i = 1, t = 1; i<= n; i++) //给地图格子编号 从1开始 变为一维处理
        for(int j = 1; j<= m; j++)
            g[i][j] = t ++;

    while(k --){
        int x1, y1, x2, y2,c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        int a = g[x1][y1], b = g[x2][y2];
        edges.insert({a, b}); edges.insert({b, a});
        if(c) add(b,a,c), add(a, b, c); //如果不是墙就建一条边
    }
    
    build();
    
    int s;
    cin >> s;
    while(s --){
        int x, y,  id;
        cin >> x >> y >> id;
        key[g[x][y]] |= 1 << id - 1; //左移一个位置让下标从0开始 节省空间？
    }
    cout << bfs() << endl;
    
    return 0;
}
#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream> //每行不知道有多少个站 所以用是sstream
using namespace std;

//每个点与后边路线的点 连一条边 表示只需要花费一趟车
//然后求1 ~ N最短路即可 换车次 = 坐车次 -1 特判一下起点终点相同的情况即可
//直接BFS即可 因为每条边的权值都是1
//注意：是有向图

/*
2021.6.9：dijkstra算法的本质也是bfs，但是会有一个v[]/st[]来判断每次队头元素是否已经被更新过
其实由于bfs的性质，第一次被已经算出的最优的元素更新之后，不会再更新此元素了，即使此点也是其他和更新他的“最优”
元素一样优的点，这样更新只是徒劳，完全没必要，所以相对于之前写过的代码，这里的bfs加上了判重，跑的更快。
*/

const int N = 510;

int n, m;
bool g[N][N];
int dist[N];
int stop[N];  //存站牌
int q[N];
bool v[N]; //新加判重

void bfs() {
    int hh = 0, tt = 0;
    memset(dist, 0x3f, sizeof dist);
    q[0] = 1, dist[1] = 0;

    while (hh <= tt) {
        int t = q[hh++];
        if (v[t]) continue;
        v[t] = 2;
        for (int i = 1; i <= n; i++)
            if (g[t][i] && dist[i] > dist[t] + 1) {
                dist[i] = dist[t] + 1;
                q[++tt] = i;
            }
    }
}

int main() {
    cin >> m >> n;
    string line;
    getline(cin, line); //回车吞掉
    while (m --) {
        getline(cin, line);
        stringstream ssin(line);
        int cnt = 0, p;
        while (ssin >> p) stop[cnt ++] = p;
        for (int j = 0; j < cnt; j++) //每个站点和它后边的站连一条边
            for (int k = j + 1; k < cnt; k++)
                g[stop[j]][stop[k]] = true;
    }

    bfs();

    if (dist[n] == 0x3f3f3f3f) cout << "NO" << endl;
    else cout << max(dist[n] - 1, 0) << endl;

    return 0;
}
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

//先把所有必选边加入并查集 产生若干个连通块 
//每个连通块看成点 然后把所有非必选的边排序 做kruskal 
//如果过程中发现某2个点已经连通 那么就跳过 不连通就正常操作
//对于某个连通块 其父节点就是整个连通块的代表节点 
//又因为判断是否连通 是判断父节点是否相同 这样并查集就自然实现了缩点的操作

const int N = 2010, M = 10010;
int n, m;
int p[N];

struct Edge{
    int a, b, w;
    bool operator< (const Edge & t) const{
        return w < t.w;
    }
}e[M];

int find(int x){
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

int main(){
    cin >> n >> m;
    for(int i = 1;i <= n; i++) p[i] = i;
    
    int res = 0, k = 0;
    for(int i = 0; i < m; i++){
        int a, b, c, t;
        cin >> t >> a >> b >> c;
        if(t == 1){
            res += c; //必选的先直接加入答案中
            p[find(a)] = find(b); //合并
        }else e[k++] = {a, b, c}; //e中只存 非必选边 
    }
    
    sort(e, e + k);
    for(int i = 0; i < k; i++){
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if(a != b){
            p[a] = b;
            res += w;
        }
    }
    
    cout << res << endl;
    
    return 0;
}
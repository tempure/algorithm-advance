#include <bits/stdc++.h>
using namespace std;

//边权从小到大排序  然后kruskal 合并集合
//每次合并2个连通块时候 需要连接2个连通块内部所有的边 原来的树肯定至少有一条边已经连通这2个块
//假设原来树连通这2 块的最小边权是 w 那么新加的边权就是w + 1
//由于计算连通块内的点数 需要维护并查集的SIZE

const int N = 6010;  //有N-1条边

int n;
struct Edge{
    int a, b , w;
    bool operator< (const Edge & t){
        return w < t.w;
    } 
}e[N];

int p[N], sz[N];

int find(int x){
    if(x!= p[x]) p[x] = find(p[x]);
    return p[x];
}

int main(){
    int t;
    cin >> t;
    while(t --){
        cin >> n;
        memset(p, 0, sizeof p);
        memset(sz, 0, sizeof sz);
        memset(e, 0, sizeof e);
        for(int i = 0; i < n - 1; i++){ //注意是 输入n - 1 条边  不是 n
            int a, b, w;
            cin >> a >> b >> w;
            e[i] = {a, b, w};
        }
        sort(e, e + n);
        for(int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
        //因为是按照原来的存在的树的边排序的，所以每次遍历到的w就是原来树的边权值
        int res = 0;
        for(int i = 0; i < n; i++){
            int a = find(e[i].a), b = find(e[i].b), w = e[i].w ;
            if(a != b){
                res += (sz[a] * sz[b] - 1) *(w + 1); //减去一个已经存在的原来的树的边
                sz[b] += sz[a];
                p[a] = b;
            }
        }
        cout <<  res << endl;
    }
    return 0;
}
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef pair<int, int> pii;
#define x first
#define y second

//寻找一个最小的d值 然后图中小于等于d的点相连 也就是删除距离大于d的边 那么就出现了若干个连通块
//如果出现连通块个数不超过 k 那么说明d合法 
//注意题意:只有 两个 点都有设备 才能进行通信
//kruskal 算法是递增求连通块的边 初始的连通块是所有点 当连通块个数递减到k时 结束 此时的边权就是答案

const int N = 510, M = N * N / 2;

int n, k, m;
int p[N];
pii q[N]; //存储所有的点

struct Edge{
    int a, b ;
    double w;
    bool operator< (const Edge & t){
        return w < t.w;
    }
}e[M];


int find(int x){
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

double get_dist(pii a, pii b){
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx *dx + dy * dy);
}

int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> q[i].x >> q[i].y;
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++) //无向边 只需要存一次即可
            e[m++] = {i, j, get_dist(q[i], q[j])};
    sort(e, e +m);

    for(int i = 0; i < n; i++) p[i] = i;
    int cnt = n; //连通块个数
    double res = 0;
    for(int i = 0; i < m; i++){ // 枚举所有边
        if(cnt <= k) break;
        int a = find(e[i].a), b = find(e[i].b);
        double w = e[i].w;
        if(a != b){
            p[a] = b;
            cnt --; //最后剩下k个连通块的时候 此时的边权就是答案
            res = w;
        }
    }

    printf("%.2f", res);

    return 0;
}
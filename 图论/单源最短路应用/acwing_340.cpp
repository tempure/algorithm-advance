#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>
using namespace std;

//单源最短路+二分
//注意题意只需要考虑一条通路即可，不是支付其余的所有路径
//也就是让路径的第k + 1 大数最小 二分x即可: 比x大的数个数是否<= k 满足则减小x
//将所有边分类：比x大边权为1 比x小则边权为0，然后双端队列BFS求最短路
//也可以用分层图 拆点来做 

const int N = 1010, M = 20010;
int n, m, k;
int h[N], e[M], ne[M], idx, w[M];
deque<int> q;
int dist[N];
bool st[N];


void add(int a, int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

bool check(int bound){
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[1] = 0;
    
    q.push_back(1);
    
    while(q.size()){
        int t = q.front();
        q.pop_front();
        
        if(st[t]) continue;
        st[t] = 1;
        
        for(int i = h[t]; i!= -1; i = ne[i]){
            int j = e[i], v = w[i] > bound; //大于的边权就是1 否则就是0
            if(dist[j] > dist[t] + v){
                dist[j] = dist[t] + v;
                if(!v) q.push_front(j);
                else q.push_back(j);
            }
        }
    }
    
    return dist[n] <= k;
}

int main(){
    
    cin >> n >> m >> k;
    memset(h, -1 ,sizeof h);
    while(m --){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b ,c); add(b, a, c);
    }
    int l  =0, r = 1e6 +1;
    while(l < r){
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    
    if(r == 1e6 + 1) r = -1;
    cout << r << endl;
    
    return 0;
}

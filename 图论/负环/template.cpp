#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

//常用2种spfa求负环的方法，常用的是第二种
//统计每个点入队的次数 如果某个点入队n次 那么存在负环
//统计当前每个点的最短路中所包含的边数 如果某个点的 最短路包含的边数>=n 那么有能说明存在负环

const int N = 510, M = 5500;

int n, m1, m2; //m1 双向边和单向边的数量
int h[N], ne[M], w[M],  e[M], idx;
int dist[N];
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

//双端队列写法 较慢
bool spfa1() {
    int hh = 0, tt = 0;
    memset(dist, 0, sizeof dist); //注意在求负环中  由于虚拟原点的思路 每个点和原点的距离 都初始化为0
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);

    for (int i = 1; i <= n; i++) {
        q[tt++] = i;
        st[i] = true; //所有点都全部入队
    }
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false; //不在队列里面就是false

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] +  1;
                if (cnt[j] >= n) return true;
                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N)  tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false; //不存在负环
}

//栈优化写法 较块 仅适用于找负环的情况，如果不是找负环则很慢
bool spfa() {
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    memset(dist, 0, sizeof dist);

    int hh = 0, tt = 0;
    for (int i = 1; i <= n; i++) {
        q[tt++] = i;
        st[i] = true; //此处意思依然为在“栈”中就是true
    }
    while (hh != tt) {
        int t = q[-- tt]; //改成栈唯一需要修改的地方 取消双端队列的写法
        // if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n) return true; //存在负环
                if (!st[j]) {
                    q[tt++] = j;
                    // if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

//差分约束 栈优化找负环 适用于差分约束
//由于差分约束会加虚拟源点同时和虚拟源点连边，导致图一定连通
//所以不必初始将所有点入队 只将虚拟源点入队即可
bool spfa3() {
    int hh = 0, tt = 1;//初始入队虚拟源点 注意下标
    memset(dist, 0xcf, sizeof dist); //求最长路 初始为负无穷 此句没有也能AC，我😅不会证明，最好加上
    dist[0] = 0;
    q[0] = 0;
    st[0] = true;

    while (hh != tt) {
        int t = q[--tt]; //队列会超时 直接改为栈优化
        // if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n + 1) return true; //存在负环 则无解 有虚拟源点的话，加上虚拟原点后是n + 1个点
                if (!st[j]) {
                    q[tt++] = j;
                    // if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

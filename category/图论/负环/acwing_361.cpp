#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

//01分数规划: 求和/求和 分式 在图论中的问题
//通用解法：二分

//注意此题边权点权值都是正数
//二分mid 满足 ∑f[i]/∑t[i] > mid 移项得 Σf[i] - mid * Σt[i] > 0 注意浮点数 不能判断相等
//由于点上也有权值 那么可以将点权放在出边上 也可以放在入边上 对于一个环来说 求和是等价的
//继续变型公式，将∑t[i] 拆开，f[i]拆开 那么每条边的权值就是f[i] - mid * t[k] 其中k是第k条 边
//这样直接转换为负环问题：如果存在一个环是正的，那么说明当前mid是符合条件的 增大mid二分
//由于是求正环是否存在 那么就把所有边权取反号 然后求负环是否存在 但是没必要这样做，可以求最长路 把不等号变号即可
//《算法竞赛进阶指南》的做法是反过来移项的 这样就直接变为求负环 不是求正环了 更加直观

const int N = 1010, M = 5010;

int n, m;
int h[N], e[M], wt[M], ne[M], idx;
int wf[N]; //点权
int q[N], cnt[N];
double dist[N];
bool st[N];

void add(int a, int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    wt[idx] = c;
    h[a] = idx ++;
}

bool check(double mid){
    memset(st, 0, sizeof st);
    memset(dist, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);

    int hh = 0, tt = 0;

    for(int i = 1; i <= n; i++) q[tt++] = i, st[i] = true;

    while(hh != tt){
        int t = q[hh++];
        if(hh == N) hh = 0;
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(dist[j] < dist[t] + wf[t] - mid * wt[i]){  //这个不等式移项之后 和书上的一模一样 本质是一样的
                // if(dist[j] > dist[t] + mid * wt[i] - wf[t]) 也是可以的 
                //dist[j] = dist[t] + mid * wt[i] - wf[t]
                dist[j] = dist[t] + wf[t] - mid * wt[i];
                cnt[j] = cnt[t] + 1;
                if(cnt[j] >= n) return true;
                if(!st[j]) {
                    q[tt++] = j;
                    if(tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

int main(){
    cin >> n >> m;
    memset(h, -1, sizeof h);

    for(int i = 1; i <= n; i++) cin >> wf[i];
    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    double l = 0, r = 1010;
    while(r - l > 1e-4){ //保留2位小数
        double mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }

    printf("%.2f\n", r);

    return 0;
}
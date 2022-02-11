#include <bits/stdc++.h>
using namespace std;


//POJ 3585 换根DP
//https://www.acwing.com/video/1966/

/*
朴素枚举每个点为root，然后进行树形DP O(N^2) 超时

换根DP: 一次DP + 一次DFS 第二次DFS称为“二次扫描同时换根”
考虑先随便选一个点为root DP一次, 临时所有子树流量保存在D[]数组
重开一个F[]，F[x]为x为root时，最大的流量，也就是最终的答案候选
然后递推与root为邻的点为根，换根后的最大流量F[]与D[]的关系，假设邻点为y
此时已经地推出y为root时候的F[],然后继续递推，这样自上而下的DFS就地推出了所有点的F[]

DP时候是自底向上的回溯，二次扫描时候是自顶向下递推
这个优化的思路其实类似于记忆化搜索，计算过的子树就不用重复计算了，虽然不是直接用搜索过的结果
但是只需要重新递推就能得到新的要求的结果
*/

const int N = 2e5 + 10, M = 2 * N;
int e[M], ne[M], idx, h[N], w[M];
bool v[N];
int d[N], f[N], deg[N], n;

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dp(int x) { //第一次DP
    v[x] = 1;
    d[x] = 0;
    for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if (v[j]) continue;
        dp(j);
        if (deg[j] == 1) d[x] += w[i];
        else d[x] += min(w[i], d[j]);
    }
    v[x] = 0; // memset超时就回溯时候清空 v
}

void dfs(int x) { //二次扫描
    v[x] = 1;
    for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if (v[j]) continue;
        f[j] = d[j];
        //三种情况讨论 D-> F递推
        if (deg[x] > 1 && deg[j] > 1)
            f[j] += min(f[x] - min(d[j], w[i]), w[i]);
        else if (deg[x] > 1 && deg[j] == 1)
            f[j] += min(f[x] - w[i], w[i]);
        else if (deg[x] == 1)
            f[j] += w[i];
        dfs(j); //尾递归 直接自上而下递推
    }
    v[x] = 0;  //如果memset 超时就回溯清空v
}

void solve() {
    //init
    memset(h, -1, sizeof h);
    memset(deg, 0, sizeof deg);
    // memset(v, 0, sizeof v); //如果超时就在回溯时候清零 不用 memset
    idx = 0;

    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
        deg[a] ++, deg[b]++;
    }
    dp(1); //1号点选为临时 root

    // memset(v, 0, sizeof v); //重新复用v[]
    f[1] = d[1];
    dfs(1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i]);
    cout << ans << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t -- ) solve();
    return 0;
}
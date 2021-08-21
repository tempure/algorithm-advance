#include <bits/stdc++.h>
using namespace std;

//https://www.acwing.com/solution/content/63860/

/*
topsort 找环即使图不联通也可以找到，毕竟非联通不影响拓扑序，非联通也有0入度的点
*/

const int N = 3e5 + 10, M = 5e5;
int h[N], e[M], ne[M], idx;
int dist[N][30];
int d[N];
typedef pair<int, int> PII;
int hh = 0, tt = -1;
bool st[N];
int q[N];
int w[N];
int n, m;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool topsort() {

    // d[i] 存储点i的入度
    for (int i = 1; i <= n; i ++ )
        if (!d[i])
            q[ ++ tt] = i;

    while (hh <= tt) {
        int t = q[hh ++ ];

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (-- d[j] == 0)
                q[ ++ tt] = j;
        }
    }

    // 如果所有点都入队了，说明存在拓扑序列；否则不存在拓扑序列。
    return tt == n - 1;
}

int main() {
    scanf("%d%d", &n, &m);
    string tmp;
    cin >> tmp;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ ) {
        int x = tmp[i - 1] - 'a';
        w[i] = x;
    }

    while (m -- ) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        d[b] ++;
    }

    //init value dp
    for (int i = 1; i <= n; i ++ ) {
        if (!d[i]) {
            dist[i][w[i]] = 1;
        }
    }

    bool flag = topsort();

    if (!flag) {
        puts("-1");
        return 0;
    }

    for (int i = 0; i <= tt; i ++ ) {
        int j = q[i];
        for (int u = h[j]; ~u; u = ne[u]) {
            int k = e[u];
            for (int v = 0; v < 26; v ++ ) {
                dist[k][v] = max(dist[k][v], dist[j][v] + (w[k] == v));
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i ++ ) {
        for (int j = 0; j < 26; j ++ ) {
            ans = max(ans, dist[i][j]);
        }
    }

    printf("%d", ans);

    return 0;
}
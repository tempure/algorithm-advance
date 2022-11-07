#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
1.用并查集保证了最后的答案一定是MST，如果必选的边不构成环
而且这种情况下而且最优解一定是MST，因为MST已经满足所有点可以互通，而且有环一定会让答案更差

2.如果必选的边能构成环，那么也无所谓，kruskal算法不会对那些成环的边有任何影响

那么就先将所有必选的边选上，将其端点加入DSU，然后再对所有边做一次MST即可

因为kruskal是贪心，也就是在已经选的所有边的情况下继续找MST，始终保持最优

此题也证明了，图中某些边已经选了的情况下，依然可以用kruskal求出最小连通代价


对于改做法的另外一种理解：首先将所有必选的边加入DSU，这样图中就有很多零散的连通块，连通块内部必然已经连通
那么只需要让这些连通块之间连通即可。
*/

const int N = 2010, M = 10010;
int n, m;
int p[N], st[N];

struct Edge {
    int p, a, b, w;
    bool operator< (const Edge & t) {
        return w < t.w;
    }
} e[M];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void solve() {
    cin >> n >> m;
    ll res = 0;
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 0; i < m; i++) {
        int a, b, w;
        int flag;
        cin >> flag >> a >> b >> w;
        e[i] = {flag, a, b, w};
        if (flag == 1) {
            p[find(a)] = find(b);
            res += w;
        }
    }

    sort(e, e + m);
    for (int i = 0; i < m; i++) {
        int a = find(e[i].a), b = find(e[i].b), flag = e[i].p, w = e[i].w;
        // if (flag == 1) continue;
        if (a != b) {
            res += w;
            p[a] = b;
        }
    }
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}
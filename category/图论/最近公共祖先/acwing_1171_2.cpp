#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 10, M = 2 * N;
int h[N], e[M], ne[M], w[M], idx;
int st[N];
int p[N], res[M], dist[N]; //p-dsu res-answer of each query, dist- dist from point to root
int n, m;

vector <pair<int, int>> query[N]; //first-query point pair second-id of query

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int find(int x) {
    if (x != p[x])p[x] = find(p[x]);
    return p[x];
}

void dfs(int u, int fa) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dist[j] = dist[u] + w[i];
        dfs(j, u);
    }
}

//st[u] = 1, 正在计算当前点的询问中，已经算出祖宗节点的那些点的询问
//st[u] = 2, u已经算出了祖先，已经和祖宗的并查集节点合并，可以用于和u有查询关系的点来被查询
//st[u] = 0, 还没搜u
//这个tarjan本质还是 dfs，用已经求出的点，也就是和该点的并查集所在子树已经合并的，那么就可以用来被查询了
//由于搜索顺序，每个询问假设是query(a,b), 那么只有2种情况：a已经搞过dsu合并了，st[a] = 2, b还没被处理过
//那么处理b的时候就会求出这个query，当处理a时候，b还没被处理，所以只有后面求b才能求这个query
//所以每个query最多只会被计算一次，不会重复

void tarjan(int u) {
    st[u] = 1; //正在搜当前点
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            tarjan(j);
            p[j] = u;
        }
    }
    for (auto item : query[u]) {
        int y = item.first, id = item.second;
        if (st[y] == 2) {
            int anc = find(y);
            res[id] = dist[u] + dist[y] - dist[anc] * 2;
        }
    }
    st[u] = 2; //当前点u已经搜完
}

void solve() {
    cin >> n >> m;
    memset(h, - 1, sizeof h);
    for (int i = 1; i <= n; i++) p[i] = i;

    for (int i = 0 ; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a != b) {
            query[a].push_back({b, i});
            query[b].push_back({a, i});
        }
    }
    dfs(1, -1);
    tarjan(1);
    for (int i = 0; i < m; i++) cout << res[i] << endl;
}

signed main() {
    solve();
    return 0;
}
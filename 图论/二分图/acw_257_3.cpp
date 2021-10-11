#include <bits/stdc++.h>
using namespace std;


/* 2021.10.11 update
注意这个二分，是最后停留在满足条件的最大的分界值，能让所有连通块都是二分图
我擦，我好想似乎到现在 都 没 有  真 正  理 解 二 分
注意是先 r = mid, 此时mid是一个符合的条件，最后的二分结束的边界是l = mid +1,然后l==r
此时就是最大的符合check(mid)的那个mid

注意此题还有一个坑点就是以某个权值dfs时候忽略 <= mid 的边的时候，此时dfs的图不一定是连通的，所以要对每个连通块都要判断一遍是否是二分图
*/

const int N = 20010, M = 200010;
int h[N], e[M], ne[M], w[M], idx;
int n, m;
int color[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool dfs(int u, int c, int mid) {
    color[u] = c;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (w[i] <= mid) continue;
        if (color[j]) {
            if (color[j] == c) return false;
        }
        else if (!dfs(j, 3 - c, mid)) return false;
    }
    return true;
}

bool check(int mid) {
    memset(color, 0, sizeof color);
    for (int i = 1; i <= n; i++) //注意图不一定连通
        if (!color[i])
            if (!dfs(i, 1, mid)) return false;
    return true;
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);

    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    //binary search
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << r << endl;
}

int main() {
    solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1000010;


int n;
int v[N], dist[N], l[N], r[N];
int ans[N];

struct Segment {
    int end, root, size;
} stk[N];

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (v[x] < v[y]) swap(x, y); //大根堆
    r[x] = merge(r[x], y);
    if (dist[r[x]] > dist[l[x]]) swap(r[x], l[x]);
    dist[x] = dist[r[x]] + 1;
    return x;
}

int pop(int x) {
    return merge(l[x], r[x]); //合并左右子树 就相当于删掉root
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        v[i] -= i;
    }
    int tt = 0;
    for (int i = 1; i <= n; i++) {
        auto cur = Segment({i, i, 1});
        dist[i] = 1;
        while (tt && v[cur.root] < v[stk[tt].root]) {
            cur.root = merge(cur.root, stk[tt].root);
            if (cur.size % 2 && stk[tt].size % 2)
                cur.root = pop(cur.root);
            cur.size += stk[tt].size;
            tt --;
        }
        stk[++tt] = cur;
    }

    for (int i = 1, j = 1; i <= tt; i++) {
        while (j <= stk[i].end)
            ans[j++] = v[stk[i].root];
    }

    ll res = 0;
    for (int i = 1; i <= n; i++) res += abs(v[i] - ans[i]);
    printf("%lld\n", res);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i] + i);

    return 0;
}
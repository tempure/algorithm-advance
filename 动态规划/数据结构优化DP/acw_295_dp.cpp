#include <iostream>
#include <algorithm>
#define l second
#define r first
#define pushup(u) tr[u].v = min(tr[u << 1].v, tr[u << 1 | 1].v)
using namespace std;

const int N = 25010, M = 1000010, INF = 1e9;
int n, m;
pair<int, int> range[M];

//POJ2376 POJ3171 ACwing295 acwing296
//就是裸的线段树，和DP感觉没啥关系。。
//https://www.acwing.com/video/1957/
//单点修改，区间查min

struct Node {
    int l, r, v;
    bool operator < (const Node w) const { //右端点还是左端点排序都能过。。。不知道为啥
        return r < w.r;
    }
} tr[M * 4];

void build(int u, int l, int r) {
    tr[u] = { l, r, INF };
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void update(int u, int k, int v) {
    if (tr[u].l == tr[u].r) tr[u].v = min(tr[u].v, v);
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (k <= mid) update(u << 1, k, v);
        else update(u << 1 | 1, k, v);
        pushup(u);
    }
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
    int mid = tr[u].l + tr[u].r >> 1;
    int res = INF;
    if (l <= mid) res = query(u << 1, l, r);
    if (r > mid) res = min(res, query(u << 1 | 1, l, r));
    return res;
}

int main() {
    cin >> n >> m;
    build(1, 0, m);
    for (int i = 0; i < n; i++) cin >> range[i].l >> range[i].r;
    sort(range, range + n);
    update(1, 0, 0);
    for (int i = 0; i < n; i++) {
        int l = range[i].l, r = range[i].r;
        int v = query(1, l - 1, r - 1) + 1;
        update(1, r, v);
    }
    int res = query(1, m, m);
    if (res == INF) res = -1;
    cout << res << endl;
    return 0;
}

// 作者：Protein
// 链接：https://www.acwing.com/activity/content/code/content/622682/
// 来源：AcWing
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
#include <iostream>
using namespace std;

//细节补充

const int N = 2e5 + 10;
int m, p;

struct Node {
    int l, r;
    int v;
} tr[N * 4];

void pushup(int u) {
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r); //一定要写成 l<=mid 考虑偶数个元素情况，此时mid是l的结尾元素,一点过要在l查询
    if (r > mid) v = max(v, query(u << 1 | 1, l, r));
    return v;
}

void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v;
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);//要写成 x<=mid,不能是<,因为mid位置元素在l的结尾，一定能要在l查
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

//初始树为空，只有modify操作才能添加元素，所以只需要建立树结构即可，不用给树节点复制，所以不用最后pushup
void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

int main() {
    int n = 0, last = 0;
    cin >> m >> p;

    build(1, 1, m); //最多加m次，也就是tr[]长度最长是m
    char op[2];
    int x;
    int l;
    while (m --) {
        scanf("%s%d", op, &x);
        if (*op == 'Q') {
            last = query(1, n - x + 1, n);
            printf("%d\n", last);
        }
        else {
            modify(1, n + 1, (last + x) % p);
            n ++;
        }
    }
    return 0;
}
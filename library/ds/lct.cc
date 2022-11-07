/*给定n个点，编号从1到n，其中第i个点的初始权值为ai。
进行m次操作，操作共分为以下4种：
0 x y，表示询问点x到点y之间的路径上的所有点（包括两端点）的权值的异或和。保证x和y之间存在连通路径。
1 x y，表示在点x和点y之间增加一条边 (x,y)。注意：如果两点已经处于连通状态，则无视该操作。
2 x y，表示删除边 (x,y)。注意：如果该边不存在，则无视该操作。
3 x w，表示将点x的权值修改为w */
const int N = 100010;
int n, m;
struct Node {
    int s[2], p, v;
    int sum, rev; //sum异或和 rev翻转标记
} tr[N];
int stk[N];
void pushrev(int x) {
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}
void pushup(int x) {
    tr[x].sum = tr[tr[x].s[0]].sum ^ tr[x].v ^ tr[tr[x].s[1]].sum;
}
void pushdown(int x) {
    if (tr[x].rev) {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
}
bool isroot(int x) { //x是否是当前splay的树根
    return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
}
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    //splay的根的父亲节点的上边是虚边 可不敢乱旋转
    if (!isroot(y)) tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int x) {
    int top = 0, r = x;
    stk[++top] = r;
    while (!isroot(r)) stk[++top] = r = tr[r].p;
    while (top) pushdown(stk[top --]);
    while (!isroot(x)) {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y))
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
}
void access(int x) { // 建立一条从根到x的路径，同时将x变成splay的根节点
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p) {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}
void makeroot(int x) {  // 将x变成原树的根节点
    access(x);
    pushrev(x);
}
int findroot(int x) { // 找到x所在原树的根节点, 再将原树的根节点旋转到splay的根节点
    access(x);
    while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];
    splay(x);
    return x;
}
void split(int x, int y) {  // 给x和y之间的路径建立一个splay，其根节点是y
    makeroot(x);
    access(y);
}
void link(int x, int y) { // 如果x和y不连通，则加入一条x和y之间的边
    makeroot(x);
    if (findroot(y) != x) tr[x].p = y;
}
void cut(int x, int y) { // 如果x和y之间存在边，则删除该边
    makeroot(x);
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> tr[i].v;
    while (m --) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 0) {
            split(x, y); //y此时是splay的根
            cout << tr[y].sum << endl;
        }
        else if (t == 1) link(x, y);
        else if (t == 2) cut(x, y);
        else {
            splay(x);
            tr[x].v = y;
            pushup(x);
        }
    }
    return 0;
}
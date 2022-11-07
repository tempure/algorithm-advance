//注意：只在查询，或者中序输出等自上而下的操作调用pushdown
/*模板题:给定一个长度为 n 的整数序列，初始时序列为 {1,2,…,n−1,n}。
序列中的位置从左到右依次标号为 1~n。
我们用 [l,r] 来表示从位置 l 到位置 r 之间（包括两端点）的所有数字构成的子序列。
现在要对该序列进行 m 次操作，每次操作选定一个子序列 [l,r]，并将该子序列中的所有数字进行翻转。
例如，对于现有序列 1 3 2 4 6 5 7，如果某次操作选定翻转子序列为 [3,6]，那么经过这次操作后序列变为 1 3 5 6 4 2 7。
请你求出经过 m 次操作后的序列。
*/
const int N = 100010;
int n, m;
struct Node {
    int s[2], p, v; //s[0]左子节点 s[1]右子节点, p父亲节点 v当前点的编号
    int size, flag; //当前点为根的子树大小 flag是否反转
    void init(int _v, int _p) { //初始化节点
        v = _v, p = _p;
        size = 1;
    }
} tr[N];
int root, idx;
void pushup(int x) { //旋转之后pushup
    //此题只需要维护size
    //左子树size+右子树size+root
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size +  1;
}
void pushdown(int x) { //递归之前向下传lazytag
    if (tr[x].flag) {
        //递归交换子节点可以实现反转整个区间
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].flag ^= 1;
        tr[tr[x].s[1]].flag ^= 1;
        tr[x].flag = 0; //下传之后清空当前点的flag
    }
}
void rotate(int x) { //左旋+右旋
    //拓扑序是 Z->Y->X
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x; // k=0表示x是y的左儿子；k=1表示x是y的右儿子 k=1右旋 否则左旋
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z; //z的子节点改为x x的父节点改为z
    //y的左节子点是x的右子节点，或者右子节点是x的左子节点 根据左右旋(k)而定
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y; //x的右(左)子节点的父亲是y
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);  //旋转之后先pushup(y) 后pushup(x)
    //此处不用push(z)因为pushup本题的操作只是维护size，而z的子树size没有改变
}
void splay(int x, int k) { //将x旋转到k的下边
    while (tr[x].p != k) {
        //拓扑序是Z->Y->X
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            //如果是折线状就旋转2次X
            //直线形状就先y后x
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x; //特判旋转后是root的情况
}
void insert(int v) {
    int u = root, p = 0;
    /*
    当前编号比u的编号大，就插在右子树，反之插在左子树
    splay所维护的信息一定满足BST性质
    比如此题维护的就是数组元素的下标满足BST
    那么下标对应元素的值就不满足BST了
    */
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0); //插入后旋到root
}
int get_k(int k) { //返回中序中的第k个数
    int u = root;
    while (true) {
        pushdown(u);
        //左子树size大于k就在左子树迭代找
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1; //没有找到
}
void output(int u) { //从根节点开始中序输出
    pushdown(u);
    if (tr[u].s[0]) output(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v <= n) printf("%d ", tr[u].v);
    if (tr[u].s[1]) output(tr[u].s[1]);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; i++) insert(i); //0,n+1是哨兵 防止RE
    while (m --) { //翻转区间的操作
        int l, r;
        scanf("%d%d", &l, &r);
        //反转的是[l,r]那么就要splay(l-1) splay(r+1)
        //但是有开头哨兵节点的存在要加上1
        l = get_k(l), r = get_k(r + 2);
        splay(l, 0), splay(r, l);
        tr[tr[r].s[0]].flag ^= 1; //旋转之后r的左子树就是要旋转的区间了 更新flag即可
    }
    output(root); //输出中序遍历
    return 0;
}
/*NOI2004《郁闷的出纳员》：有几种操作:
I 命令，格式为 I_k，表示新建一个工资档案，初始工资为 k。如果某员工的初始工资低于工资下界，他将立刻离开公司。
A 命令，格式为 A_k，表示把每位员工的工资加上 k。
S 命令，格式为 S_k，表示把每位员工的工资扣除 k。
F 命令，格式为 F_k，表示查询第 k 多的工资。
对于每次询问输出，以及最后输出离职人数。
用Splay维护所有员工工资的BST,由于是对所有区间元素增加或者减小 直接记录一个偏移量delta即可
每次扣除工资操作就删除前缀小于 m - delta 的区间删去即可
查询就是最基本的BST查询，维护size即可
*/
const int N = 100010, INF = 0x3f3f3f3f;
int n, m, delta;
struct Node {
    int s[2], p, v;
    int size;
    void init(int _v, int _p) {
        v = _v, p = _p;
        size = 1;
    }
} tr[N];
int root, idx;
void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}
int insert(int v) {
    int u = root, p = 0;
    //插入是每个点的val满足BST 不是节点的tr数组编号
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
    return u; //返回该点的tr数组编号
}
int lower_bound_(int v) { //返回val大于等于v的节点编号
    int u = root, res;
    while (u) {
        if (tr[u].v >= v) res = u, u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return res;
}
int get_k(int k) { //返回第k小的val
    int u = root;
    while (u) {
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 ==  k) return tr[u].v;
        else k -= tr[tr[u].s[0]].size + 1,  u = tr[u].s[1];
    }
    return -1; //没找到
}
int main() {
    scanf("%d%d", &n, &m);
    int L = insert(-INF), R = insert(INF); //哨兵 返回tr数组中的编号
    int tot = 0; //insert的员工总数量
    while (n --) {
        char op[2];
        int k;
        scanf("%s%d", op, &k);
        if (*op == 'I') {
            if (k >= m) k -= delta, insert(k), tot ++; //新员工的工资要先减去当前的偏移量，因为偏移量已经算上了该员工之前的加减工资操作
        }
        else if (*op == 'A') delta += k;
        else if (*op == 'S') {
            delta -= k;
            R = lower_bound_(m - delta); //R是>=m-delta的第一个数的编号
            splay(L, 0), splay(R, L); //这里的删除怎么写都行 只要记住L的中序肯定在R左边即可
            tr[R].s[0] = 0;
            pushup(R), pushup(L); //删去节点之后 要先pushup下边的节点 后pushup上边的
        }
        else {
            if (tr[root].size - 2 < k) puts("-1");
            else printf("%d\n", get_k(tr[root].size - k) + delta);
        }
    }
    printf("%d\n", tot - (tr[root].size - 2)); //减去哨兵 以及现存的人 就是离职的人数
    return 0;
}
/*HNOI2012《永无乡》：永无乡包含 n 座岛，编号从 1 到 n ，每座岛都有自己的独一无二的重要度，按照重要度可以将这 n 座岛排名，名次用 1 到 n 来表示。
某些岛之间由巨大的桥连接，通过桥可以从一个岛到达另一个岛。如果从岛 a 出发经过若干座（含 0 座）桥可以到达岛 b ，则称岛 a 和岛 b 是连通的。
现在有两种操作：
B x y 表示在岛 x 与岛 y 之间修建一座新桥。
Q x k 表示询问当前与岛 x 连通的所有岛中第 k 重要的是哪座岛，即所有与岛 x 连通的岛中重要度排名第 k 小的岛是哪座，请你输出那个岛的编号。
n<=100000,m<=n,q<=300000
用DSU维护所有splay的关系,初始每一个点就是一颗splay,然后合并
合并为启发式合并，size小的splay的所有点暴力dfs插入size大的splay中
本质上就是把小的splay的所有点复制一份插入大的splay然后更新并查集的p[]祖宗关系
每次查询只会查询祖宗节点所在DSU节点的root，也就是说，将小的splay插入到大的splay
之后，查询原来小的splay中的id时，find()函数返回的root会定位到合并之后的大的splay
*/
const int N = 1800010;//启发式合并的数量上限是 O(nlogn)，每次合并时均新增节点，所以总节点数应为n+nlogn
int n, m;
struct Node {
    int s[2], p, v, id;
    int size;
    void init(int _v, int _id, int _p) {
        v = _v, id = _id, p = _p;
        size = 1;
    }
} tr[N];
int root[N], idx; //root[]记录每一颗splay的根节点
int p[N]; //DSU的祖宗节点
int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}
void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}
void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int x, int k, int b) { //将b集合的x旋转到k下
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root[b] = x;
}
void insert(int v, int id, int b) { //将id的点插入b集合
    int u =  root[b], p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, id, p);
    splay(u, 0, b);
}
int get_k(int k, int b) { //返回集合b中val第k小的id
    int u = root[b];
    while (u) {
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return tr[u].id;
        else k -=  tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}
void dfs(int u, int b) { //将u所在的集合所有点插入b集合
    if (tr[u].s[0]) dfs(tr[u].s[0], b);
    if (tr[u].s[1]) dfs(tr[u].s[1], b);
    insert(tr[u].v, tr[u].id, b);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        p[i] = root[i] = i;
        int v;
        scanf("%d", &v);
        tr[i].init(v, i, 0);
    }
    idx = n;
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        a = find(a), b = find(b);
        if (a != b) {
            if (tr[root[a]].size > tr[root[b]].size) swap(a, b);
            dfs(root[a], b);
            p[a] = b;
        }
    }
    scanf("%d", &m);
    while (m --) {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        if (*op == 'B') {
            a = find(a), b = find(b);
            if (a != b) {
                if (tr[root[a]].size > tr[root[b]].size) swap(a, b);
                dfs(root[a], b);
                p[a] = b;
            }
        }
        else {
            a = find(a);
            if (tr[root[a]].size < b) puts("-1");
            else printf("%d\n", get_k(b, a));
        }
    }
    return 0;
}
/*NOI2005《维护数列》：维护一个序列（最少有一个数）
INSERT posi tot在当前第posi个数字后面插入tot个数字
DELETE posi tot在当前第posi个数字开始连续删除tot个数字
MAKE-SAME posi tot c连续tot个改为相同的数c
REVERSE posi tot 翻转posi开始的tot个数这一段
GET-SUM posi tot 计算posi开始的tot个数的序列和
MAX-SUM 求出当前序列的最大连续子段和
添加/删除一段直接旋转然后操作即可，对于删除此题用到内存回收技巧，复用删除掉的点。最大子段和与线段树处理思路一致分类讨论，修改就是直接打懒标记。翻转操作和模板的稍有区别注意。
*/
const int N = 500010, INF = 1e9;
int n, m;
struct Node {
    int s[2], p, v;
    int rev, same; //lazytag 翻转 变成同一个数
    int size, sum, ms, ls, rs; //区间和/最大子段和/最大前缀和/最大后缀和
    void init(int vv, int pp) {
        s[0] = s[1] = 0, p = pp, v = vv;
        rev = same = 0;
        size = 1, sum = ms = v;
        ls = rs = max(v, 0);
    }
} tr[N];
int root;
int nodes[N], tt; //内存（节点）回收数组
int w[N]; //初始的数组用来build建树
void pushup(int x) {
    auto &u = tr[x], &l = tr[u.s[0]], &r = tr[u.s[1]];
    u.size = l.size + r.size + 1;
    u.sum = l.sum + r.sum + u.v;
    u.ls = max(l.ls, l.sum + u.v + r.ls); //最大前缀
    u.rs = max(r.rs, r.sum + u.v + l.rs);
    u.ms = max(max(l.ms, r.ms), l.rs + u.v + r.ls);
}
void pushdown(int x) {
    auto &u = tr[x], &l = tr[u.s[0]], &r = tr[u.s[1]];
    if (u.same) {
        u.same = u.rev = 0; //全部变为一个数rev翻转无意义
        if (u.s[0]) l.same = 1, l.v = u.v, l.sum = l.v * l.size;
        if (u.s[1]) r.same = 1, r.v = u.v, r.sum = r.v * r.size;
        if (u.v > 0) {
            if (u.s[0]) l.ms = l.ls = l.rs = l.sum;
            if (u.s[1]) r.ms = r.ls = r.rs = r.sum;
        }
        else {
            if (u.s[0]) l.ms = l.v, l.ls = l.rs = 0;
            if (u.s[1]) r.ms = r.v, r.ls = r.rs = 0;
        }
    }
    else if (u.rev) {
        //注意交换的是前后缀，不是简单交换所有的节点信息
        //所以先交换前后缀然后单纯交换"子节点的子节点"
        //到子节点的子节点pushdown的时，直接交换前后缀即可
        u.rev = 0, l.rev ^= 1, r.rev ^= 1;
        swap(l.ls, l.rs), swap(r.ls, r.rs);
        swap(l.s[0], l.s[1]), swap(r.s[0], r.s[1]);
    }
}
int build(int l, int r, int p) { //p是建的树的root节点
    int mid = l + r >> 1;
    int u = nodes[tt--];
    tr[u].init(w[mid], p);
    if (l < mid) tr[u].s[0] = build(l, mid - 1, u);
    if (mid < r) tr[u].s[1] = build(mid + 1, r, u);
    pushup(u);
    return u;
}
void rotate(int x) { //左旋+右旋
    //拓扑序是 Z->Y->X
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x; // k=0表示x是y的左儿子；k=1表示x是y的右儿子 k=1右旋 否则左旋
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z; //z的子节点改为x x的父节点改为z
    //y的左节子点是x的右子节点，或者右子节点是x的左子节点 根据左右旋(k)而定
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y; //x的右(左)子节点的父亲是y
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);  //旋转之后先pushup(y) 后pushup(x)
    //此处不用push(z)因为pushup本题的操作只是维护size，而z的子树size没有改变
}
void splay(int x, int k) { //将x旋转到k的下边
    while (tr[x].p != k) {
        //拓扑序是Z->Y->X
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            //如果是折线状就旋转2次X
            //直线形状就先y后x
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x; //特判旋转后是root的情况
}
int get_k(int k) { //返回中序第k大的元素编号
    int u = root;
    while (u) {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
}
void dfs(int u) { //内存回收
    if (tr[u].s[0]) dfs(tr[u].s[0]);
    if (tr[u].s[1]) dfs(tr[u].s[1]);
    nodes[++tt] = u;
}
int main() {
    for (int i = 1; i < N; i++) nodes[++tt] = i;
    scanf("%d%d", &n, &m);
    tr[0].ms = w[0] = w[n + 1] = -INF;  //0号是哨兵
    for (int i = 1; i <=  n; i++) scanf("%d", &w[i]);
    root = build(0, n + 1, 0);
    char op[20];
    while (m --) {
        scanf("%s", op);
        if (!strcmp(op, "INSERT")) {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            for (int i = 0; i < tot; i++) scanf("%d", &w[i]);
            int l = get_k(posi + 1), r = get_k(posi + 2);
            splay(l, 0), splay(r, l);
            int u = build(0, tot - 1, r);
            tr[r].s[0] = u;
            pushup(r), pushup(l);
        }
        else if (!strcmp(op, "DELETE")) {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            dfs(tr[r].s[0]); //删除节点内存回收
            tr[r].s[0] = 0;
            pushup(r), pushup(l);
        }
        else if (!strcmp(op, "MAKE-SAME")) {
            int posi, tot, c;
            scanf("%d%d%d", &posi, &tot, &c);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            auto &son = tr[tr[r].s[0]];
            //修改操作打 lazy tag
            son.same = 1, son.v = c, son.sum = c * son.size;
            if (c > 0) son.ms = son.ls = son.rs = son.sum;
            else son.ms = c, son.ls = son.rs = 0; //最少一个数
            pushup(r), pushup(l);
        }
        else if (!strcmp(op, "REVERSE")) {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            auto &son = tr[tr[r].s[0]];
            son.rev ^= 1;
            swap(son.ls, son.rs);
            swap(son.s[0], son.s[1]);
            pushup(r), pushup(l);
        }
        else if (!strcmp(op, "GET-SUM")) {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            printf("%d\n", tr[tr[r].s[0]].sum);
        }
        else printf("%d\n", tr[root].ms); //最大连续子段和
    }
    return 0;
}
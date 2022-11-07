//(1)朴素并查集：
int p[N]; //存储每个点的祖宗节点
// 返回x的祖宗节点
int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}
// 初始化，假定节点编号是1~n
for (int i = 1; i <= n; i ++ ) p[i] = i;
// 合并a和b所在的两个集合：
p[find(a)] = find(b);

//(2)维护size的并查集：
int p[N], size[N];
//p[]存储每个点的祖宗节点, size[]只有祖宗节点的有意义，表示祖宗节点所在集合中的点的数量
// 返回x的祖宗节点
int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}
// 初始化，假定节点编号是1~n
for (int i = 1; i <= n; i ++ ) {
    p[i] = i;
    size[i] = 1;
}
// 合并a和b所在的两个集合：
size[find(b)] += size[find(a)];
p[find(a)] = find(b);

//(3)维护到祖宗节点距离的并查集：
int p[N], d[N];
//p[]存储每个点的祖宗节点, d[x]存储x到p[x]的距离
// 返回x的祖宗节点
int find(int x) {
    if (p[x] != x) {
        int u = find(p[x]);
        d[x] += d[p[x]];
        p[x] = u;
    }
    return p[x];
}
// 初始化，假定节点编号是1~n
for (int i = 1; i <= n; i ++ ) {
    p[i] = i;
    d[i] = 0;
}
// 合并a和b所在的两个集合：
p[find(a)] = find(b);
d[find(a)] = distance; // 根据具体问题，初始化find(a)的偏移量

/*
例题:连通块中点的数量
给定一个包含n个点（编号为1~n）的无向图，初始时图中没有边。
现在要进行m个操作，操作共有三种：
“C a b”，在点a和点b之间连一条边，a和b可能相等
“Q1 a b”，询问a和b是否在同一个连通块中，a和b可能相等
“Q2 a”，询问点a所在连通块中点的数量
第一行输入整数n和m, 1 <= n, m <= 1e5
接下来m行，每行包含一个操作指令，指令为“C a b”，“Q1 a b”或“Q2 a”中的一种。
输出格式
对于每个询问指令”Q1 a b”，如果a和b在同一个连通块中，则输出“Yes”，否则输出“No”
对于每个询问指令“Q2 a”，输出一个数表示点a所在连通块中点的数量
*/
const int N = 100010;
int p[N], size[N];
int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}
int main() {
    int n, m, a, b;
    scanf("%d%d", &n, &m);
    char s[2];
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        size[i] = 1;
    }
    while (m--) {
        scanf("%s", s);
        if (s[0] == 'C') {
            scanf("%d%d", &a, &b);
            if ( find(a) == find(b)) continue;
            //注意需要先更新size再合并 如果先合并 size就错了
            size[find(b)] += size[find(a)];
            p[find(a)] = find(b);
        } else if (s[1] == '1') {
            scanf("%d%d", &a, &b);
            if (find(a) == find(b)) puts("Yes");
            else puts("No");
        } else {
            scanf("%d", &a);
            printf("%d\n", size[find(a)]);
        }
    }
    return 0;
}


/*
例题：假设x1,x2,x3,…代表程序中出现的变量，给定n个形如xi=xj或xi≠xj的变量相等/不等的约束条件，请判定是否可以分别为每一个变量赋予恰当的值，使得上述所有约束条件同时被满足。
例如，一个问题中的约束条件为：x1=x2，x2=x3，x3=x4，x1≠x4，这些约束条件显然是不可能同时被满足的，因此应判定为不可被满足。
现在给出一些约束满足问题，请分别对它们进行判定。
输入文件的第1行包含1个正整数t，表示需要判定的问题个数，注意这些问题之间是相互独立的。
对于每个问题，包含若干行：
第1行包含1个正整数n，表示该问题中需要被满足的约束条件个数。
接下来n行，每行包括3个整数i,j,e，描述1个相等/不等的约束条件，相邻整数之间用单个空格隔开。若e=1，则该约束条件为xi=xj；若e=0，则该约束条件为xi≠xj。
*/
//离散化+DSU
//最多只有2e6个点 但是点下标最大1e9 所以要离散化
//保序离散化是排序+判重+二分 不需要保序的直接map/哈希表
//此题的离散化不需要保序 直接map即可
const int N = 2000010;
int n, m;
int p[N];
unordered_map<int, int> S;
struct Query {
    int x, y, e;
} query[N]; //存放离散化之后的询问的下标
int get(int x) {
    if (S.count(x) == 0) S[x] = ++n;
    return S[x];
}
int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}
int main() {
    int t;
    scanf("%d", &t);
    while (t --) {
        n = 0;
        S.clear();
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            int x, y, e;
            scanf("%d%d%d", &x, &y, &e);
            query[i] = {get(x), get(y), e}; //加入的时候离散化
        }
        //n就是离散化之后所有的点的个数
        for (int i = 1; i <= n; i++) p[i] = i; //初始化DSU
        //合并所有相等的约束条件
        for (int i = 0; i < m; i++) {
            if (query[i].e == 1) {
                int pa = find(query[i].x), pb = find(query[i].y);
                p[pa] = pb;
            }
        }
        //检查所有不等条件
        bool has_conflict = false;
        for (int i = 0; i < m; i++)
            if (query[i].e == 0) {
                int pa = find(query[i].x), pb = find(query[i].y);
                if (pa == pb) {
                    has_conflict = true;
                    break;
                }
            }
        if (has_conflict) puts("NO");
        else puts("YES");
    }
    return 0;
}
/*找出欧拉回路，即图中找一个环使每条边都在环上出现恰好一次
第一行包含一个整数 t，t∈{1,2}，如果 t=1表示无向图t=2表示有向图
第二行包含两个整数 n,m，表示图的结点数和边数。
接下来m行中，第i行两个整数vi,ui,表示第i条边,从1开始
如果 t=1 则表示 vi 到 ui 有一条无向边。
如果 t=2 则表示 vi 到 ui 有一条有向边。
图中可能有重边也可能有自环,点的编号从 1 到 n*/
//无向图：连通图 而且所有点度数都是偶数
//有向图：连通图 而且所有点的入度等于出度
//一般没必要加删表头的优化 但是小概率会被卡掉
//欧拉回路和孤立点没有关系 只和边有关系
const int N = 100010, M = 400010;//无向图 二倍边
int h[N], e[M], ne[M], idx;
bool used[M]; //标记边是否被用过
int ans[M], cnt; //cnt记录答案路径的长度
int din[N], dout[N]; //度数
int type;
int n, m;
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
void dfs(int u) {
    while (h[u] != -1) {
        int i = h[u];
        if (used[i]) {
            h[u] = ne[i]; //删边
            continue;
        }
        h[u] = ne[i];
        used[i] = true;
        if (type == 1) used[i ^ 1] = true; //无向图标记反向边
        dfs(e[i]);
        //加边时候第一条边的编号是0开始 但是题目是边从1开始
        if (type == 1) {
            int t = i / 2 + 1; //边的编号 t 加成对的边 但输入只输一条
            if (i & 1) t *= -1; //边的编号奇数 反向边 从0开始成对加
            ans[++cnt] = t;
        }
        else ans[++cnt] = i + 1;
    }
}
int main() {
    scanf("%d", &type);
    scanf("%d%d", &n, &m);
    memset(h, -1 , sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        if (type == 1) add(b, a);
        din[b] ++, dout[a] ++;
    }
    //提前判断无解的情况
    if (type == 1) {
        for (int i = 1; i <= n; i++)
            if (din[i] + dout[i] & 1) {
                puts("NO");
                return 0;
            }
    }
    else {
        for (int i = 1; i <= n; i++)
            if (din[i] != dout[i]) {
                puts("NO");
                return 0;
            }
    }
    //找一个包含边的起点
    for (int i = 1; i <= n; i++)
        if (h[i] != -1) {
            dfs(i);
            break;
        }
    if (cnt < m) { //有孤立边
        puts("NO");
        return 0;
    }
    puts("YES");
    for (int i = cnt ; i ; i --) printf("%d ", ans[i]);
    puts("");
    return 0;
}
/*给出n个单词，是否能首尾相连成一个串,T组测试数据。
每组数据第一行包N盘子数量。接N行，每行一个小写字母字符串单词,单词可出现多次*/
//26个字母作为点 然后单词作为边 求是否存在欧拉路径 注意这是有向图 因为字母是点
//除了起点终点 其余点都满足出度等于入度 而且所有边都连在一起(dfs/并查集) 判断连通即可
//单词中间的字母不用标记(可证明不影响正确性) 只需标记端点的2个字母
const int N = 30;//26个字母的点
int n, m;
int p[N];
bool st[N];
int din[N], dout[N];
int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}
int main() {
    char str[1010];
    int t;
    cin >> t;
    while (t --) {
        scanf("%d", &n);
        memset(din, 0, sizeof din);
        memset(dout, 0, sizeof dout);
        memset(st, 0, sizeof st);
        for (int i = 0; i < 26; i++) p[i] = i; //初始化并查集
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            int len = strlen(str);
            int a = str[0] - 'a', b = str[len - 1] - 'a';
            st[a] = st[b] = true;//该点存在于所有单词中
            dout[a] ++, din[b] ++;
            p[find(a)] = find(b);
        }
        int start = 0, end = 0;
        bool success = true;
        for (int i = 0; i < 26; i++)
            if (din[i] != dout[i]) {
                if (din[i] == dout[i] + 1) end ++;
                else if (din[i] + 1 == dout[i]) start++;
                else {
                    success = false;
                    break;
                }
            }
        //如果上边的if没有进入 说明所有点都是入度==出度
        //有多个起点和终点 那就无解
        if (success && !(!start && !end || start == 1 && end == 1)) success = false;
        //判断连通性
        int rep = -1;
        for (int i = 0; i < 26; i++)
            if (st[i]) { //判断是否存在孤立边
                if (rep == -1) rep = find(i);
                else if (rep != find(i)) {
                    success = false;
                    break;
                }
            }
        if (success) puts("Ordering is possible.");
        else puts("The door cannot be opened.");
    }
    return 0;
}
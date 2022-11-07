/*给定一个N*M的数字矩阵A，矩阵中的元素属于{0,1}。
在矩阵中找到一个行的集合，使得这些行中，每一列有且仅有一个1。
输入格式:第一行包含两个整数N和M。
接下来 N 行，每行包含 M 个整数（0 或 1），表示完整的数字矩阵。
输出格式:如果能找到,在一行中依次输出这些行的编号（行编号1~N)。
如果不唯一则以任意顺序输出任意方案,否则输出 No Solution!。*/
const int N = 5510;//所有1的数量加上第0行的head表头 注意模板没有列的表头
int n, m;
//l每个点的左边的节点 r右边的节点 d下边的 u上边的 s该列有多少个1 row点的行坐标 col列坐标
int l[N], r[N], u[N], d[N], s[N], row[N], col[N], idx;
int ans[N], top;
void init() { //初始化表头 表头一共以m + 1个点，最左边一个是哨兵 比列数多一列
    for (int i = 0; i <= m; i++) {
        l[i] = i - 1, r[i] = i + 1;
        u[i] = d[i] = i;
    }
    l[0] = m, r[m] = 0; //循环链表
    idx = m + 1; //点的内存分配指针
}
void add(int &hh, int &tt, int x, int y) {//(x,y)插入一个点
    row[idx] = x, col[idx] = y, s[y]++;
    //每次都是插到第0行表头的下边一行 是头插
    //hh tt每一行最左边2个指针，插入到这2个指针中间
    u[idx] = y, d[idx] =  d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx ++; //tt向左移动到新加入的点的位置
}
void remove(int p) { //删除第p列 以及该列有1的所有的行
    r[l[p]] = r[p], l[r[p]] = l[p];  //删除列只需要删除表头即可
    //下边的这个二重循环，并没有删除第p列的元素，只删除了表头
    for (int i = d[p]; i != p; i = d[i])
        for (int j = r[i]; j != i; j = r[j]) {
            //删除一行 修改该行的每个元素的上下指针即可
            s[col[j]] --;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
}
void resume(int p) { //恢复一次remove的所有删除
    for (int i = u[p]; i != p; i = u[i])
        for (int j = l[i]; j != i; j = l[j]) {
            u[d[j]] = j, d[u[j]] = j;
            s[col[j]] ++;
        }
    r[l[p]] = p, l[r[p]] = p;
}
bool dfs() {
    if (!r[0]) return true; //第0行链表头右边已经被删完了 说明所有的列都已经被覆盖
    int p = r[0];
    for (int i = r[0]; i; i = r[i]) //找出1最少的一列 注意不要混淆r[]和row[]
        if (s[i] < s[p])
            p = i;
    remove(p); //先删去这个表头 表示这一列已经被覆盖 因为搜的时候只会找表头
    for (int i = d[p]; i != p; i = d[i]) { //遍历当前1最少的列的每一个1所在的行，每一行都横向遍历删除列
        ans[++top] = row[i]; //记录答案
        //删除该行除了当前被覆盖的列以外，其余所有1所在的列以及该列有1的所有行
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if (dfs()) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top --;
    }
    resume(p); //恢复现场 恢复表头
    return false;
}
int main() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= n;  i++) { //读取所有点
        int hh = idx, tt = idx; //头插指针
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            if (x) add(hh, tt, i, j); //是1就插入
        }
    }
    if (dfs()) {
        for (int i = 1; i <= top; i++) cout << ans[i] << ' ';
        cout << endl;
    }
    else cout << "No Solution!" << endl;
    return 0;
}
/*《数独》:16*16的数独填写，使得每行、每列、每个4*4十六宫格内字母A~P均恰好出现一次。保证每个输入只有唯一解决方案。输入包含多组测试用例。
每组测试包括 16 行，共16个字符串。第i个字符串表示第i行。字符串包含字符为A~P或-（表示等待填充）
行代表所有格子可能填的情况，16*16*16 每个格子能填16种
列是所有的约束条件：
1.每个格子只能填一个数 一共16*16
2.每行都是0~15只填一个 一共16*16
3.列和条件2相同 一共16*16
4.每个宫也是只能0~15各填一个  一共16*16
所以有4096行1024列但是1的个数是稀疏的：
只考虑每一行中1可能出现的最多次数即可，每一行代表一个格子选择的字母，因为只是“一个格子,一个字母”，所以在4种列的约束条件中，每一种都最多只会出现一次。
举例子就是一个格子，不可能在“每个格子恰好填一个数”这一类中出现2次，也不可能在“每行0~15恰好出现一次”中出现2次，其余的约束条件同理。
所以一行中“最多”只会出现4次1，那么最多的1的点个数就是4096 * 4，加上表头的1024 + 1个点，开18000即可*/
const int N = 18000; //每行最多4个点，4096+1024+1个1最多
int m = 16 * 16 * 4; //列数
int u[N], d[N], l[N], r[N], s[N], col[N], row[N], idx;
int ans[N], top;
struct Op {
    int x, y; //坐标
    char z; //该坐标填的字母
} op[N];
char g[20][20];
void init() {
    for (int i = 0; i <= m; i++) {
        l[i] = i - 1, r[i] = i + 1;
        s[i] = 0;
        d[i] = u[i] = i;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}
void add(int &hh, int &tt, int x, int y) {
    row[idx] = x, col[idx] = y, s[y] ++;
    u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx ++;
}
void remove(int p) {
    r[l[p]] = r[p], l[r[p]] = l[p];
    for (int i = d[p]; i != p; i = d[i])
        for (int j = r[i]; j != i; j = r[j]) {
            s[col[j]] --;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
}
void resume(int p) {
    for (int i = u[p]; i != p; i = u[i])
        for (int j = l[i]; j != i; j = l[j]) {
            u[d[j]] = j, d[u[j]] = j;
            s[col[j]] ++;
        }
    r[l[p]] = p, l[r[p]] = p;
}
bool dfs() {
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[i] < s[p])
            p = i;
    remove(p);
    for (int i = d[p]; i != p; i = d[i]) {
        ans[ ++ top] = row[i];
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if (dfs()) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top -- ;
    }
    resume(p);
    return false;
}
int main() {
    while (cin >> g[0]) {
        for (int i = 1; i < 16; i++) cin >> g[i];
        init();
        for (int i = 0, n = 1; i < 16; i++) //n是行号
            for (int j = 0; j < 16; j++) {
                int a = 0, b = 15;
                //一个位置已填好就让a和b是已经填的字母
                if (g[i][j] != '-') a = b = g[i][j] - 'A';
                for (int k = a; k <= b; k++, n ++) { //枚举该位置填什么
                    int hh = idx, tt = idx;
                    op[n] = {i, j, k + 'A'};
                    add(hh, tt, n, i * 16 + j + 1); //加1是因为行列下标都从1开始
                    add(hh, tt, n, 256 + i * 16 + k + 1);
                    add(hh, tt, n, 256 * 2 + j * 16 + k + 1);
                    add(hh, tt, n, 256 * 3 + (i / 4 * 4 + j / 4) * 16 + k + 1); //每个宫0到15
                }
            }
        dfs();
        for (int i = 1; i <= top; i++) {
            auto t = op[ans[i]];
            g[t.x][t.y] = t.z;
        }
        for (int i = 0; i < 16; i++) puts(g[i]);
        puts("");
    }
    return 0;
}
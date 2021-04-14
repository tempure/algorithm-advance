/*
例题：给定 n 个长度不超过 50 的由小写英文字母组成的单词，以及一篇长为 m 的文章。请问，有多少个单词在文章中出现了。
第一行包含整数 T，表示共有 T 组测试数据。对于每组数据，第一行一个整数 n，接下去 n 行表示 n 个单词，最后一行输入一个字符串，表示文章。
1 <= n <= 1e4, 1 <= m <= 1e6
*/
//AC自动机处理next的逻辑就是用当前节点的next来同时更新子节点的next 同时延长前后缀匹配
const int N = 10010, S = 55;
const int M = 1000010;
int n, tr[N * S][26]; //trie
int cnt[N * S]; //每个节点结尾的单词的数量
char str[M];
int q[N * S]; //bfs宽搜队列
int ne[N * S];
int idx; //trie idx
void insert() {
    int p = 0; //根节点
    for (int i = 0; str[i]; i ++) {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++idx;
        p = tr[p][t];
    }
    cnt[p] ++;
}
//bfs构建AC自动机
void build() {
    int hh = 0, tt = -1;
    for (int i = 0 ; i < 26; i++) {
        //将根节点的子节点全部入队 就是第一层
        if (tr[0][i]) q[++tt] = tr[0][i];
    }
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int &c = tr[t][i];
            //trie图优化：
            //如果j的子节点c不存在 那么就让c直接指向最终的位置
            //这里的ne[]此时是递归定义的，如果匹配下一个字母失败，就会直接跳到最终的位置
            //不会在每一个fail指针处都判断是否存在该字母
            if (!c)  tr[t][i] = tr[ne[t]][i];
            else {
                //如果子节点c存在 那就和朴素的写法一样 更新子节点的next
                ne[c] = tr[ne[t]][i];
                q[++tt] = c;
            }
        }
    }
}
int main() {
    int T;
    cin >> T;
    while (T --) {
        memset(tr, 0, sizeof tr);
        idx = 0;
        memset(cnt, 0, sizeof cnt);
        memset(ne, 0, sizeof ne);
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            insert();
        }
        build();
        scanf("%s", str); //待匹配的长串
        int res = 0;
        for (int i = 0, j = 0; str[i]; i++) {
            int t = str[i] - 'a';
            //trie图优化:
            j = tr[j][t];  //不用再while循环了
            int p = j;
            while (p) { //会破坏复杂度
                res += cnt[p];
                cnt[p] = 0;
                p = ne[p];
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
/*
例题:每个单词分别在论文中出现多少次。第一行一个整数 N，表示有多少个单词。接下来 N 行每行一个单词，单词中只包含小写字母。
输入：
3
a
aa
aaa
输出：
6
3
1
*/
//题意是每个单词在所有单词出现的次数 不是一个长串进行匹配
/*
    一个单词如果不是其他单词的字串 那么就是一次
    如果是其他串的子串，那就统计后缀
    总共的次数是所有的“前缀的后缀就是原串”的后缀总数+原来串
    计算方法:逆向来算,对于每个后缀 求出与之对应的前缀 也就是ne数组处理
    ne[i], ne[ne[i]], ne[ne[ne[i]]]....这样就会处理一个串的所有 与后缀匹配的前缀
    假设f[i]表示i结尾的单词的出现的次数 那直接把f[i]加到f[ne[i]]上去
    因为单词都是在trie的树根连接的 也就是trie的前缀，一个后缀出现了n次，与之对应的前缀就出现了n次
    与后缀匹配的前缀在ne数组已经预处理好了，由fail指针的定义，i向ne[i]连边，图中不会出现环
    直接按照拓扑序从下往上树根处递推，最后枚举一下所有单词，也就是和树根连接的这些，求和即可
*/
const int N = 1000010;
int n;
int tr[N][26], idx;
int f[N]; //每个单词出现的次数
int q[N], ne[N]; //q[]是bfs队列
char str[N];
int id[210]; //每个单词对应的节点下标
void insert(int x) {
    int p = 0;
    for (int i = 0; str[i] ; i++) {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++idx;
        p = tr[p][t];
        f[p] ++; //这里统计的是前缀而不是每个单词的结尾，因为单词会出现 其他单词中 每个字母都算
    }
    id[x] = p; //这里id记录的是每个单词结尾的节点号
}
void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i++)
        if (tr[0][i]) q[++tt] = tr[0][i];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int &p = tr[t][i];
            if (!p) p = tr[ne[t]][i];
            else {
                ne[p] = tr[ne[t]][i];
                q[++tt] = p;
            }
        }
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(i);
    }
    build();
    //从树底部网上拓扑序遍历 那么bfs的倒序就是拓扑序
    for (int i = idx - 1; i >= 0; i--) f[ne[q[i]]] += f[q[i]];
    for (int i = 0; i < n; i++) printf("%d\n", f[id[i]]);
    return 0;
}
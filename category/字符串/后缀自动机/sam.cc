/*给定一个长度为n只包含小写字母的字符串S,对于所有 S 的出现次数不为 1 的子串，设其value为该子串出现的次数乘该子串的长度,求value的最大值。
用每个状态代表的节点的endpos集合大小乘该集合的longest更新即可,注意dfs的时候，要将link边反向*/
typedef long long ll;
const int N = 2000010; //SAM点开2倍
int tot = 1, last = 1; //从1开始
struct Node {
    //fa是link的节点
    //len就是longest最长的串的长度
    int len, fa;
    int ch[26]; //该节点的出边字母集合
} node[N];
char str[N];
ll f[N], ans; //f[i]就是节点i的endpos集合大小
int h[N], e[N], ne[N], idx; //link tree 邻接表存
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
void dfs(int u) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        dfs(e[i]);
        f[u] += f[e[i]]; //维护该节点的endpos
    }
    if (f[u] > 1) ans = max(ans, f[u] * node[u].len);
}
void extend(int c) {
    int p = last, np = last = ++tot;
    f[tot] = 1; //先加上前缀特殊情况
    node[np].len = node[p].len + 1;
    for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
    if (!p) node[np].fa = 1;
    else {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1) node[np].fa = q;
        else { //开新的点，复制
            int nq = ++tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
        }
    }
}
int main() {
    scanf("%s", &str);
    for (int i = 0; str[i]; i ++) extend(str[i] - 'a');
    memset(h, - 1, sizeof h);
    for (int i = 2; i <= tot; i++) add(node[i].fa, i);//反向边
    dfs(1);
    printf("%lld", ans);
    return 0;
}
/*LOJ171《Multiple LCS》求n个字符串的最长公共子串
将第一个串建SAM，然后后边的串和第一个匹配
开一个now数组，每匹配一个串 就更新一次
每次匹配失败，就跳到link后缀的node继续匹配，然后重新计算长度
每次匹配一个串之后，要dfs一遍，用子节点来更新father节点*/
const int N = 20010;
int n;
int tot = 1, last = 1;
char str[N];
struct Node {
    int len, fa;
    int ch[26];
} node[N];
//now是每次匹配一个串后每个节点的临时状态
int ans[N], now[N];
int h[N], e[N], ne[N], idx;
void extend(int c) {
    int p = last, np = last = ++tot;
    node[np].len = node[p].len + 1;
    for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
    if (!p) node[np].fa = 1;
    else {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1) node[np].fa = q;
        else {
            int nq = ++ tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
        }
    }
}
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
void dfs(int u) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        dfs(e[i]);
        now[u] = max(now[u], now[e[i]]);
    }
}
int main() {
    scanf("%d", &n);
    scanf("%s", &str); //第一个串建为SAM
    for (int i = 0; str[i]; i++) extend(str[i] - 'a');
    for (int i = 1; i <= tot; i++) ans[i] = node[i].len;
    memset(h, - 1, sizeof h);
    for (int i = 2; i <= tot; i++) add(node[i].fa, i);
    for (int i = 0; i < n - 1; i++) {
        scanf("%s", str);
        memset(now, 0, sizeof now);
        int p = 1, t = 0; //t是目前的节点longest长度
        for (int j = 0; str[j]; j++) {
            int c = str[j] - 'a';
            while (p > 1 && !node[p].ch[c]) p = node[p].fa, t = node[p].len;
            if (node[p].ch[c]) p = node[p].ch[c], t++;
            now[p] = max(now[p], t); //更新当前的每个node
        }
        dfs(1); //每个节点向其link后缀传递信息维护
        //ans存的是上一个串的每个node信息，和当前node要取min才是公共字串长度
        for (int j = 1; j <= tot; j++) ans[j] = min(ans[j], now[j]);
    }
    int res  = 0;
    //全部匹配之后从所有node的长度取max
    for (int i = 1; i <= tot; i++) res = max(res, ans[i]);
    printf("%d\n", res);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
SAM模板

给定一个长度为 n 的只包含小写字母的字符串 S。
对于所有 S 的出现次数不为 1 的子串，设其 value 值为该子串出现的次数 × 该子串的长度。
请计算，value 的最大值是多少

每个状态代表的节点的endpos集合大小x该集合的longest更新即可
dfs的时候，要将link边反向
*/

const int N = 2000010; //SAM点开2倍

int tot = 1, last = 1; //从1开始
struct Node {
    int len, fa; //len就是longest最长的串的长度 fa是link的节点
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
    for (int i = 2; i <= tot; i++) add(node[i].fa, i); //加反向边

    dfs(1);
    printf("%lld", ans);

    return 0;
}
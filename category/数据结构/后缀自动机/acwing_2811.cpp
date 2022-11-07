#include <bits/stdc++.h>
using namespace std;

/*
将第一个串建SAM，然后后边的串和第一个匹配
开一个now数组，每匹配一个串 就更新一次
每次匹配失败，就跳到link后缀的node继续匹配，然后重新计算长度
这里匹配的本质就是用SAM中的node来匹配每一个串，匹配的过程中维护node保存的最值

注意每次匹配一个串之后，要dfs一遍，用子节点来更新father节点
*/

const int N = 20010;

int n;
int tot = 1, last = 1;
char str[N];//模板开2倍空间

struct Node {
    int len, fa;
    int ch[26];
} node[N];

int ans[N], now[N]; //now是每次匹配一个串后每个节点的临时状态
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
        //下边较长的串节点来更新fa节点
        now[u] = max(now[u], now[e[i]]);
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s", &str); //第一个串建为SAM
    for (int i = 0; str[i]; i++) extend(str[i] - 'a');
    //初始node[]的最大值就是endpos的最长串长度
    for (int i = 1; i <= tot; i++) ans[i] = node[i].len;
    memset(h, - 1, sizeof h);
    //注意parent tree上的边建图dfs是反向的
    //但是struct中保存的不是反向的
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
    for (int i = 1; i <= tot; i++) res = max(res, ans[i]); //全部匹配之后从所有node的长度取max
    printf("%d\n", res);

    return 0;
}
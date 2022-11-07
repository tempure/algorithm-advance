#include <bits/stdc++.h>
using namespace std;

/*2021.9.17 更新

https://www.luogu.com.cn/blog/user29936/solution-p3825
https://studyingfather.blog.luogu.org/solution-p3825

理解需要注意的地方就是，如果某个限制条件，第一个位置能满足，但是第二个位置却满足不了，那么这个限制依然还是作废

如果第i场游戏的地图适合型号为hi的赛车，
但第j场游戏的地图不适合型号为hj的赛车，那么建边u−>u′，
表示如果第i场游戏使用了型号为hi的赛车则一定无解。
*/

//===================================old content==============================//

/*
此题如果没有x位置，那就是裸的2-SAT
考虑到x最多只有8个，直接暴力枚举所有的x位置的可能组合
x位置转换为2-SAT：用“不选A”以及“不选B”作为一个x位置的正反命题即可
这2个命题可以包含所有的选"A B C" 的选项

对于字符串中的每个位置，假设该位置是'a'，那么意味着赛车只能放'B''C'
a往后加一在模3的意义下就是B，转换为大小写相同之后，那么B为命题0，C为命题1
将所有的命题0编号为0~n-1，命题1编号为n~2n-1 也就是一正一反命题
如果求完SCC之后存在"需要同时选择一个位置的2个赛车可选项",那就矛盾了，说明无解
*/

const int N = 100010, M = 200010; //n场比赛每场分2个点

int n, d, m;
char s[N];
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], stk[N], top, ts;
int id[N], cnt;
bool ins[N];
int pos[10]; //记录x的位置

struct Op { //每个约束条件
    int x, y; //约束的i j
    char a, b; //hi hj
} op[M];

int get(int x, char b, int t) { //得到点的编号
    //t==0代表正命题 t==1代表反命题
    //点0~n-1表示正命题 n~2n~1表示逆命题
    char a = s[x] - 'a';
    b -= 'A';
    if (((a + 1) % 3 != b) ^ t) return x + n;
    return x;
}

char put(int x, int t) { //对应编号的字母
    int y = s[x] - 'a';
    return 'A' + ((y + t) % 3);
}

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    stk[++top] = u, ins[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (ins[j]) low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u]) {
        int y;
        cnt++;
        do {
            y = stk[top --], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}

bool work() {
    memset(h, -1, sizeof h);
    memset(dfn, 0, sizeof dfn);
    idx = ts = cnt = 0;

    for (int i = 0; i < m; i++) { //枚举所有约束条件 建边
        int x = op[i].x - 1,  y = op[i].y - 1; //场次从1开始 这里转换为0开始 字符串s是从0开始的
        char a = op[i].a, b = op[i].b;
        if (s[x] != a + 32) {
            /*
            对于约束(i,hi,j,hj) 字符串s的i位置如果和hi不矛盾这个约束才会有用
            比如某个位置已经是'a' 约束是“假设该位置放a”，那么这个约束就没用
            所以只需要考虑有用的约束，用if判断(s[x] != a + 32)即可,注意大小写字母的转换
            */
            if (s[y] != b + 32) add(get(x, a, 0), get(y, b, 0)), add(get(y, b, 1), get(x, a, 1));
            /*
            如果i和hi的约束满足，但是j和hj与原字符串s矛盾了 那就只能将约束条件1取反了
            意思是第i场不能安排hi赛车
            */
            else add(get(x, a, 0), get(x, a, 1));
        }
    }

    for (int i = 0; i < n * 2; i++)
        if (!dfn[i])
            tarjan(i);

    for (int i = 0; i < n; i++)
        if (id[i] == id[i + n])
            return false;

    for (int i = 0; i < n; i++) //输出方案
        if (id[i] < id[i + n]) putchar(put(i, 1));
        else putchar(put(i, 2));

    return true;
}

int main() {
    scanf("%d%d", &n, &d);
    scanf("%s", s);
    for (int i = 0, j = 0; i < n; i++)
        if (s[i] == 'x') //记录所有x的位置
            pos[j++] = i;

    scanf("%d", &m);
    for (int i = 0; i < m; i++) //所有的约束条件
        scanf("%d %c %d %c", &op[i].x, &op[i].a, &op[i].y, &op[i].b);

    for (int k = 0; k < 1 << d; k++) { //枚举所有x的组合方式
        for (int i = 0; i < d; i++)
            if (k >>  1 & 1) s[pos[i]] = 'a';
            else s[pos[i]] = 'b';

        if (work()) return 0; //每个x的状态都重新建图 求解
    }

    puts("-1");
    return 0;
}
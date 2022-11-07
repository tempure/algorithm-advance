#include <bits/stdc++.h>
using namespace std;

/*
f[i][0]表示不选i 能选的最多点数
f[i][1]表示选i 能选的最多点数

对于i的子节点j:
1.不选i 那么j可选可不选 f[i][0] = ∑max{f[j][0], f[j][1]}
2.选i 那么要从i的子节点中选一个来限制i, f[i][1]可以用f[i][0]的部分来计算
枚举子节点j来限制i，也就是除了j其他的子节点都可选可不选 但是j必不选 要用来限制
f[i][1] = max{f[i][0] - max(f[j][1],f[j][0]) + f[j][0] + 1}

注意特判断开环的特殊位置 拆开边u->j之后，要补上u和j之间的转移关系
1.u不用j来限制
2.u用j来限制
*/

const int N = 1000010, INF = 1e8;

int n;
int h[N], e[N], rm[N], ne[N], idx;
int f1[N][2], f2[N][2];
bool st[N], ins[N];
int ans;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs_f(int u, int ap, int f[][2]) { //必选ap
    for (int i = h[u]; i != -1; i = ne[i]) {
        if (rm[i]) continue;
        int j = e[i];
        dfs_f(j, ap, f);
        f[u][0] += max(f[j][0], f[j][1]);
    }

    //此处要特判一下断开的特殊位置 此时u只被j限制 则u在断开后的树中的子节点可选可不选
    //且u是一定要选的 那么u不选的状态就设为-INF
    if (u == ap) f[u][1] = f[u][0] + 1, f[u][0] = -INF;
    else {
        f[u][1] = -INF;
        for (int i = h[u]; i != -1; i = ne[i]) {
            if (rm[i]) continue;
            int j = e[i];
            //不是断开的特殊位置 也就是普通位置
            //选了u 那么从u的子节点里面枚举一个 来限制u 选了u那么点数加1
            f[u][1] = max(f[u][1], f[u][0] - max(f[j][0], f[j][1]) + f[j][0] + 1);
        }
    }
}

void dfs_c(int u, int from) { //dfs找环
    st[u] = ins[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) dfs_c(j, i);
        else if (ins[j]) {
            rm[i] = 1; //删边

            //此时断开的边为 u->j
            dfs_f(j, -1, f1); //不用j来限制u, j可选可不选
            dfs_f(j, u, f2); //只用j来限制u, 必不选j 必选u
            ans += max(max(f1[j][0], f1[j][1]), f2[j][0]);
        }
    }
    ins[u] = false;
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        add(a, i); //建立外向树
    }

    for (int i = 1; i <= n; i++)
        if (!st[i])
            dfs_c(i, -1);
    printf("%d\n", ans);

    return 0;
}
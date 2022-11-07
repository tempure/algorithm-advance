#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

/*
这个题还是比较有意思的，你需要证明的就是这个题本质就是求树的直径那题，可以dfs也可以树形DP
仔细考虑一下求树的直径那道题，维护的就是树上每个点向下走的最大和次大路径权值，你想一下如果从底部向上走，
当前的权值和减去边权为负数了，那么我们可以直接丢弃掉从底部叶子节点到这个点的这段路径，因为它的贡献为负。

所以题目中的条件“在经过任何一条边之前，你的现有能量都不能少于该边所需消耗的能量（否则，将无法顺利通过该边）”
这个条件在dfs维护的过程中是肯定会考虑到的，dfs当前点初始 max1,max2 最大以及次大路径都是0，你减为负数肯定比max1,2都小
那么此时依然保持 max1,2都是0，相当于直接不要下面那一段路径。
*/

const int N = 300010, M = N * 2;

int n;
int v[N];
int h[N], e[M], w[M], ne[M], idx;
LL f[N];
LL ans;

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

//f[u] 为从树底部向上走到当前节点 u 的最大路径权值
void dfs(int u, int fa) {
    LL max1 = 0, max2 = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        //更新向下的最大和次大路径
        if (f[j] - w[i] >= max1) {
            max2 = max1;
            max1 = f[j] - w[i];
        }
        else if (f[j] - w[i] > max2) {
            max2 = f[j] - w[i];
        }
    }

    ans = max(ans, v[u] + max1 + max2);
    f[u] = v[u] + max1;
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &v[i]);

    for (int i = 0; i < n - 1; i ++ ) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }

    dfs(1, -1);

    printf("%lld\n", ans);
    return 0;
}
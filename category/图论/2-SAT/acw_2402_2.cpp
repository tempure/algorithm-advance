#include <bits/stdc++.h>
using namespace std;

//update 2021.9.15 It seems I understand more about the 2-SAT lol.....
//espacially the output answer method, it's not GREEDY algorithm, it's has the correctness of proof

/*
首先2-SAT跑完 Tarjan SCC 后的图一定是对称的拓扑图，也就意味着，如果要选一个SCC中的某个点，那么该SCC的
所有点都要选，也就是说，在一个SCC中，如果存在A--->B的边，那么如果选A，也就必须要选B点

考虑SCC之间的边，也就是缩点后的拓扑图上的点之间的边，这样的边同样存在，选x必须选y的性质
因为当初加边时候，所有的边都是根据这种性质来加的。

考虑缩点之后的点A--->B，如果选A点所在的SCC，那么必然会选B所在的SCC，但是一个重要的性质是
如果选了B，那么就不一定选A点所在的SCC，如果选了拓扑图靠前的点，那么一定要接着选拓扑图边相连的SCC，
但是如果我们选拓扑序靠后的点，就不再有什么累赘了，直接继续确定选接下来的点。

为啥选了拓扑序前面的点，然后此时必然要连环选后面的缩后点，这样会导致错误...我的感性理解：

假设缩点后的2对点为 A前，A后，B前，B后
1.如果都选前，但是拓扑图中却存在 A前-->B后，也就是大致拓扑位置为 B前....--> A前-->B后....--->A后
  这样显然错了，因为正确的选法是选了A前，那么B后必选

2.如够都选靠后的点，即使最特殊的情况 A后-->B前.....-->B后，那么即使选了A后，不选B前，而是选B后，那么也是满足拓扑序的
这样是对的
*/

const int N = 2000010, M = 2000010; //每对关系都要连2条

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts, stk[N], top;
int id[N], cnt;
bool ins[N];

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

    if (low[u] == dfn[u]) {
        int y;
        cnt ++;
        do {
            y = stk[top --], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int i, a, j, b;
        // cin >> i >> a >> j >> b; //这题卡输入 wdnmd
        scanf("%d%d%d%d", &i, &a, &j, &b);
        i--; j-- ; //编号改为从0开始
        add(2 * i + !a, 2 * j + b); //非A->B
        add(2 * j + !b, 2 * i + a); //非B->A
    }

    for (int i = 0; i < n * 2; i++)
        if (!dfn[i]) tarjan(i);

    for (int i = 0; i < n; i++)
        if (id[i * 2] == id[i * 2 + 1]) {
            puts("IMPOSSIBLE");
            return;
        }
    puts("POSSIBLE");
    for (int i = 0; i < n; i++)
        //2 * i代表假 2 * i + 1代表真
        if (id[i * 2] < id[i * 2 + 1]) printf("0 ");
        else printf("1 ");
}

int main() {
    solve();
    return 0;
}
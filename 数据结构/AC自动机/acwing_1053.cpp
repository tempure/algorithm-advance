#include <iostream>
#include <cstring>
using namespace std;


const int N = 1010;
int n, m;
int tr[N][4];
int dar[N]; //标记trie中结尾的当前单词 是致病DNA
int q[N],  ne[N];
int idx;
char str[N];

int f[N][N]; //状态 f[i][j] 在长串的第i个位置 在trie上的第j个节点的状态 删除的最少字符的个数

int get(char c) {
    if (c == 'A') return 0;
    if (c == 'T') return 1;
    if (c == 'G') return 2;
    return 3;
}

void insert() {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int t = get(str[i]);
        if (!tr[p][t]) tr[p][t] = ++idx;
        p = tr[p][t];
    }
    dar[p] = 1;
}

void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 4; i++)
        if (tr[0][i]) q[++tt] = tr[0][i];

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 4; i++) {
            int p = tr[t][i];
            if (!p) tr[t][i] = tr[ne[t]][i];
            else {
                ne[p] = tr[ne[t]][i];
                q[++tt] = p;
                dar[p] |= dar[ne[p]]; //当前后缀是危险片段 那么与之对应的前缀肯定是危险片段
            }
        }
    }
}

int main() {
    int T = 1;
    while (scanf("%d", &n), n) {
        memset(tr, 0, sizeof tr);
        memset(dar, 0, sizeof dar);
        memset(ne, 0, sizeof ne);
        idx = 0;

        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            insert();
        }

        build();

        scanf("%s", str + 1);
        m = strlen(str + 1);

        memset(f, 0x3f, sizeof f);
        f[0][0] = 0;

        //DP
        for (int i = 0; i < m; i++)
            for (int j = 0; j <= idx; j++)
                for (int k = 0; k < 4; k++) {
                    int t = get(str[i + 1]) != k;
                    int p = tr[j][k];
                    if (!dar[p]) f[i + 1][p] = min(f[i + 1][p], f[i][j] + t);
                }

        int res = 0x3f3f3f3f;
        for (int i = 0; i <= idx; i++) res = min(res, f[m][i]);
        if (res == 0x3f3f3f3f) res = -1;
        printf("Case %d: %d\n", T++, res);
    }

    return 0;
}


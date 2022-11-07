#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, idx;
int tr[N][26];
int f[N];
int q[N], ne[N];
char str[N];
int id[210];

void insert(int x) {
    int p = 0;
    for (int i = 0; str[i]; i ++) {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++idx;
        p = tr[p][t];
        f[p]++; //这个前缀出现过的次数
    }
    id[x] = p;
}

//建图之后，所有的点都在 queue 中
void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i++)
        if (tr[0][i]) q[++tt] = tr[0][i];

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int &p = tr[t][i]; //只有有字符串中字符的点才会入队
            if (!p) p = tr[ne[t]][i];
            else {
                ne[p] = tr[ne[t]][i];
                q[++tt] = p;
            }
        }
    }
}

void solve() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str); //复用 str[N]
        insert(i);
    }
    build();
    // idx - 1 开始是因为 队列 q[] 下标从0开始，一共有 idx 个点在队列中
    for (int i =  idx - 1; i >= 0; i--) f[ne[q[i]]] += f[q[i]];
    for (int i =  0; i < n; i++) printf("%d\n", f[id[i]]);
}

int main() {
    solve();
    return 0;
}
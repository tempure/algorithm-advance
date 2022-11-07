#include <bits/stdc++.h>
using namespace std;


/*2021 9.16 update
用0~n-1号点表示所有婚礼选开始部分，n~2n-1号点 表示所有婚礼的后半段选择

注意如果和前面冲突那就和后面连，和后面冲突就和前面连边
这样逻辑可以保证如果前后都冲突的话，那么一定一个婚礼的前后段都在同一个SCC中,判定为无解
*/

//=============================== old content ============================================//

/*
每个婚礼选择首段还是尾段2段看成2个变元
判断所有婚礼对的组合的相交关系，假设婚礼ab，a的开头和b的开头相交，那么选择a的开头则必须选择b的尾段
判断4个关系连边，0 ~ n - 1为所有婚礼的开头 n - 1 ~ 2n - 1为所有婚礼的结尾段
*/

const int N = 2010, M = 4000010;

int n;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts, stk[N], top;
int id[N], cnt;
bool ins[N];

struct Wedding {
    int s, t, d; //开始 结束 耗时
} w[N];

bool is_overlap(int a, int b, int c, int d) {
    return d > a  && b > c; //判断 ab线段和cd是否相交
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
        cnt ++;
        do {
            y = stk[top --], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; i++) {
        int s0, s1, t0, t1, d;
        scanf("%d:%d %d:%d %d", &s0, &s1, &t0, &t1, &d);
        w[i] = {s0 * 60 + s1, t0 * 60 + t1, d}; //转化为分钟计算
    }

    for (int i = 0; i < n; i++) //枚举所有的婚礼对 加边
        for (int j = 0; j < i; j++) {
            auto a = w[i], b = w[j];
            if (is_overlap(a.s, a.s + a.d, b.s, b.s + b.d)) add(i, j + n), add(j, i + n);
            if (is_overlap(a.s, a.s + a.d, b.t - b.d, b.t)) add(i, j), add(j + n, i + n);
            if (is_overlap(a.t - a.d, a.t, b.s, b.s + b.d)) add(i + n, j + n), add(j, i);
            if (is_overlap(a.t - a.d, a.t, b.t - b.d, b.t)) add(i + n, j), add(j + n, i);
        }
    for (int i = 0; i < n * 2; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 0; i < n; i++)
        if (id[i] == id[i + n]) {
            puts("NO");
            return 0;
        }

    puts("YES");

    for (int i = 0; i < n; i++) {
        auto a = w[i];
        int s = a.s, t = a.t, d = a.d;
        if (id[i] < id[i + n])
            printf("%02d:%02d %02d:%02d\n",  s / 60, s % 60, (s + d) / 60, (s + d) % 60);
        else printf("%02d:%02d %02d:%02d\n", (t - d) / 60, (t - d) % 60, t / 60, t % 60);
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

//麻了，板子改了半天不知道哪里出锅了，直接把样例输出，得不到正确解
//https://github.com/livrth/libra/blob/master/ds/dlx_exact_cover.cc

const int N = 18000; //每行最多4个点，4096+1024+1个1最多
int m = 9 * 9 * 4; //列数
int u[N], d[N], l[N], r[N], s[N], col[N], row[N], idx;
int ans[N], top;
struct Op {
    int x, y; //坐标
    char z; //该坐标填的字母
} op[N];
char g[20][20];
void init() {
    for (int i = 0; i <= m; i++) {
        l[i] = i - 1, r[i] = i + 1;
        s[i] = 0;
        d[i] = u[i] = i;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}
void add(int &hh, int &tt, int x, int y) {
    row[idx] = x, col[idx] = y, s[y] ++;
    u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx ++;
}
void remove(int p) {
    r[l[p]] = r[p], l[r[p]] = l[p];
    for (int i = d[p]; i != p; i = d[i])
        for (int j = r[i]; j != i; j = r[j]) {
            s[col[j]] --;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
}
void resume(int p) {
    for (int i = u[p]; i != p; i = u[i])
        for (int j = l[i]; j != i; j = l[j]) {
            u[d[j]] = j, d[u[j]] = j;
            s[col[j]] ++;
        }
    r[l[p]] = p, l[r[p]] = p;
}
bool dfs() {
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[i] < s[p])
            p = i;
    remove(p);
    for (int i = d[p]; i != p; i = d[i]) {
        ans[ ++ top] = row[i];
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if (dfs()) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top -- ;
    }
    resume(p);
    return false;
}
int main() {
    for (int i = 0; i < 1; i++) {
        for (int i = 0; i < 9; i++) cin >> g[i];
        init();
        for (int i = 0, n = 1; i < 9; i++) //n是行号
            for (int j = 0; j < 9; j++) {
                int a = 0, b = 8;
                //一个位置已填好就让a和b是已经填的字母
                if (g[i][j] != '0') a = b = g[i][j] - '0';
                for (int k = a; k <= b; k++, n ++) { //枚举该位置填什么
                    int hh = idx, tt = idx;
                    op[n] = {i, j, k + '0'};
                    add(hh, tt, n, i * 9 + j + 1); //加1是因为行列下标都从1开始
                    add(hh, tt, n, 81 + i * 9 + k + 1);
                    add(hh, tt, n, 81 * 2 + j * 9 + k + 1);
                    add(hh, tt, n, 81 * 3 + (i / 4 * 4 + j / 4) * 9 + k + 1); //每个宫0到15
                }
            }
        dfs();
        for (int i = 1; i <= top; i++) {
            auto t = op[ans[i]];
            g[t.x][t.y] = t.z;
        }
        for (int i = 0; i < 9; i++) puts(g[i]);
        puts("");
    }
    return 0;
}
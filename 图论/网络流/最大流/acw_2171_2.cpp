#include <bits/stdc++.h>
using namespace std;

//EK O(N*M^2)
//残留网络建图

const int N = 1010, M = 20010, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], idx;
int f[M];
int d[N];
int pre[N];
bool st[N];
int q[N];

void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(st, false, sizeof st);
    q[0] = S, st[S] = true, d[S] = INF;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int ver = e[i];
            if (!st[ver] && f[i]) {
                st[ver] = true;
                d[ver] = min(f[i], d[t]);
                pre[ver] = i;
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

int ek() {
    int r = 0;
    while (bfs()) {
        r += d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1])
            f[pre[i]] -= d[T], f[pre[i] ^ 1] += d[T];
    }
    return r;
}

void solve() {
    cin >> n >> m >> S >> T;
    memset(h, -1, sizeof h);
    while (m -- ) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    cout << ek() << endl;
}

int main() {
    solve();
    return 0;
}
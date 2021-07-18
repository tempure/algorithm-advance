//求最大匹配数，匈牙利算法，O(N*M)
bool dfs(int u) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (st[j]) continue;
        st[j] = true;
        int t = mc[j];
        if (t == 0 || dfs(t)) {
            mc[j] = u;
            return true;
        }
    }
    return false;
}

void solve() {
    while (cin >> n && n) {
        cin >> m >> k;
        idx = 0;
        memset(h, -1, sizeof h);
        memset(mc, 0, sizeof mc);

        while (k --) {
            int a, b , t;
            cin >> t >> a >> b;
            if (!a || !b) continue;
            add(a, b);
        }

        int res = 0;
        for (int i = 1; i < n; i++) {
            memset(st, 0, sizeof st);
            if (dfs(i)) res++;
        }
        cout << res << endl;
    }
}

//染色法判断二分图
bool dfs(int u, int c) { //c表示把u染成c颜色1,2两种颜色之一
    color[u] = c;
    for (int i =  h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!color[j]) {
            if (!dfs(j, 3 - c)) return false;
        } else if (color[j] == c) return false;
    }
    return true;
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b); add(b, a);
    }

    bool flag = true;
    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            if (!dfs(i, 1)) {
                flag = false;
                break;
            }
        }
    }
    if (flag) puts("Yes");
    else puts("No");

    return 0;
}
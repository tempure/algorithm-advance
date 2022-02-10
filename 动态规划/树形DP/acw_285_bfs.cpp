#include <bits/stdc++.h>
using namespace std;


//N过大DFS爆栈的话
//改为自底向上拓扑排序写法 O(N)

const int N = 6010;
vector<int> fa[N];
int f[N][2], v[N], h[N], n;
int in[N]; //degree
queue<int> q;

void dp() {
    for (int i = 1; i <= n; i++)
        if (in[i] == 0) q.push(i);
    for (int i = 1; i <= n; i++) f[i][1] = h[i];
    while (q.size()) {
        auto t = q.front();
        q.pop();
        for (auto x : fa[t]) {
            f[x][0] += max(f[t][0], f[t][1]);
            f[x][1] += f[t][0];
            if (--in[x] == 0) q.push(x);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v[x] = 1; //x has a father node y
        in[y] ++;
        fa[x].push_back(y);
    }
    int root;
    for (int i = 1; i <= n; i++)
        if (!v[i]) {
            root  = i;
            break;
        }
    dp();
    cout << max(f[root][0], f[root][1]);
    return 0;
}
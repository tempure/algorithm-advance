#include <bits/stdc++.h>
using namespace std;

//2022.2.10
//lyd 蓝书写法 DFS 实现树形DP O(N)

const int N = 6010;
vector<int> son[N];
int f[N][2], v[N], h[N], n;

void dp(int x) {
    f[x][0] = 0;
    f[x][1] = h[x];
    for (int i = 0; i < son[x].size(); i++) {
        int y = son[x][i];
        dp(y);
        f[x][0] += max(f[y][0], f[y][1]); //dont choose this node
        f[x][1] += f[y][0]; //choose this node
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v[x] = 1; //x has a father node
        son[y].push_back(x);
    }
    int root;
    for (int i = 1; i <= n; i++)
        if (!v[i]) {
            root  = i;
            break;
        }
    dp(root);
    cout << max(f[root][0], f[root][1]);
    return 0;
}
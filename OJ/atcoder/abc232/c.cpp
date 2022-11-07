#include <bits/stdc++.h>
using namespace std;

//判断图同构 O(N^2 * N!)

int main() {
    int n, m;
    cin >> n >> m;
    vector x(n, vector<bool>(n)), y(n, vector<bool>(n));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a -= 1, b -= 1;
        x[a][b] = x[b][a] = true;
    }
    for (int i = 0; i < m; ++i) {
        int c, d;
        cin >> c >> d;
        c -= 1, d -= 1;
        y[c][d] = y[d][c] = true;
    }
    vector<int> p(n);
    iota(begin(p), end(p), 0);
    int ans = 0;
    do {
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (x[i][j] != y[p[i]][p[j]]) {
                    ok = false;
                }
            }
        }
        if (ok) {
            cout << "Yes\n";
            return 0;
        }
    } while (next_permutation(begin(p), end(p)));
    cout << "No\n";
}
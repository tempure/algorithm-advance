#include <bits/stdc++.h>
using namespace std;
//谜语题
int main() {
    int n, m; cin >> n >> m;
    bool ok = true;
    string ans(n, '0');
    bool used[n] = {};
    for (int i = 0; i < m; i++) {
        int s; cin >> s;
        char c; cin >> c;
        if (!used[s - 1]) {
            ans[s - 1] = c;
            used[s - 1] = true;
        } else if (ans[s - 1] != c) {
            ok = false;
        }
    }
    if (n > 1 and ans[0] == '0') {
        if (used[0]) ok = false;
        else ans[0] = '1';
    }
    cout << (ok ? ans : "-1");
}
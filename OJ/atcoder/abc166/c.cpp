#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n, m, x, y;
    cin >> n >> m;
    int h[n + 1], flag[n + 1], ans = 0;
    fill(flag, flag + n + 1, 1);
    for (int i = 1; i <= n; i++) cin >> h[i];
    while (m--) {
        cin >> x >> y;
        if (h[x] <= h[y]) flag[x] = 0;
        if (h[y] <= h[x]) flag[y] = 0;
    }
    for (int i = 1; i <= n; i++)
        if (flag[i]) ans++;
    cout << ans;
    return 0;
}
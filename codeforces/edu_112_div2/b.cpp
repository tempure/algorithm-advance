#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x1, y1, x2, y2, W, H, w, h;
    cin >> W >> H;
    cin >> x1 >> y1 >> x2 >> y2;
    cin >> w >> h;

    int ans = 0x3f3f3f3f;
    if (x2 - x1 + w <= W) {
        ans = min(ans, max(0, w - x1)); //左边空隙
        ans = min(ans, max(0, x2 - (W - w))); //右边空隙
    }
    if (y2 - y1 + h <= H) {
        ans = min(ans, max(0, h - y1));
        ans = min(ans, max(0, y2 - (H - h)));
    }
    if (ans == 0x3f3f3f3f)
        cout << -1.000000 << endl;
    else
        printf("%.6lf\n", (double)ans);
}

int main() {
    int t;
    cin >> t;
    while (t --) solve();
    return 0;
}
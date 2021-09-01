#include <bits/stdc++.h>
using namespace std;

void solve() {
    int l, r;
    int last = 0;
    int n;
    cin >> n;
    while (n --) {
        cin >> l >> r;
        if (max(last, l) > r) cout << 0 << ' ';
        else {
            cout << max(last, l) << ' ';
            last = max(last, l) + 1;
        }
    }
    puts("");
}

int main() {
    int t;
    cin >> t;
    while (t --) solve();
    return 0;
}
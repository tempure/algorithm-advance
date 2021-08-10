#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 1e5 + 10;
int a[N];

void solve() {
    memset(a, 0, sizeof a);
    int n, k;
    cin >> n >> k;
    // cout << k << endl;
    int cnt = 0;
    int max = -2e9;
    a[0] = -2e9;
    int min = 2e9;
    bool flag = true;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (a[i] < a[i - 1]) {
            if (a[i - 1] > max) max = a[i - 1];
            if (a[i] < min) min = a[i];
            cnt++;
        }
        int tmp1 = a[i];
        while (i + 1 <= n && a[i + 1] >= a[i]) i++;
        int tmp2 = a[i];
        if (tmp2 <= min || tmp1 >= max) {
            continue;
        }
        else {
            cnt++;
        }
        // if (tmp1 < max && tmp2 > max) {
        //     cnt += 1;
        // }
    }
    // cout << cnt << ' ';
    if (cnt> k) puts("No");
    else puts("Yes");
    // cout << k << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
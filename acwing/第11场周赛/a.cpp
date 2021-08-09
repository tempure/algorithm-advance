#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    int a[4];
    int n = 4;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    a[0] = a[3] - a[0];
    a[1] = a[3] - a[1];
    a[2] = a[3] - a[2];
    sort(a, a + 3);
    for(int i = 0; i< 3; i++) cout << a[i] << ' ';
}


int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
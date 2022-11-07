#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 2e5 + 10;
pii a[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a + 1, a + 1 + n);
    cout << a[n-1].second << endl;
}



int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());
    int cnt = 1;
    for (int i = 1; i < n; i++)
        if (v[i - 1].second + 1 != v[i].second)
            cnt++;
    if (cnt > k) puts("NO");
    else puts("YES");
}

int main() {
    int t = 1;
    cin >> t;
    while (t --)solve();
    return 0;
}
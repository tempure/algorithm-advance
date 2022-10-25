#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int res = 1e9;
    for (int i = 1; i < n; i++) res = min(res, abs(a[i] - a[i - 1]));
    res = min(res, abs(a[n - 1] - a[0]));
    cout << res << endl;

    return 0;
}
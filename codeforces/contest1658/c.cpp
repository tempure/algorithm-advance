#include <bits/stdc++.h>
using namespace std;

//算是个比较抽象的题。。。
//https://codeforces.com/blog/entry/101302

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &v : a) cin >> v;
    if (count(a.begin(), a.end(), 1) != 1) {
        cout << "NO\n";
        return;
    }
    int p = find(a.begin(), a.end(), 1) - a.begin();
    rotate(a.begin(), a.begin() + p, a.end());
    for (int i = 1; i < n; ++i) {
        if (a[i] - a[i - 1] > 1) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
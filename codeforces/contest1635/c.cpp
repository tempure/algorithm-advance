#include <bits/stdc++.h>
using namespace std;

//https://codeforces.com/blog/entry/100153
//这场怎么全是证明题。。。。

int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector <int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        if (a[n - 2] > a[n - 1]) {
            cout << -1 << endl;
        } else {
            if (a[n - 1] < 0) {
                if (is_sorted(a.begin(), a.end())) {
                    cout << 0 << endl;
                } else {
                    cout << -1 << endl;
                }
            } else {
                cout << n - 2 << endl;
                for (int i = 1; i <= n - 2; ++i) {
                    cout << i << ' ' << n - 1 << ' ' << n << endl;
                }
            }
        }
    }
}
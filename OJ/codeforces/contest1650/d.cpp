#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define forn(i, n) for (int i = 0; i < int(n); i++)


void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int ans[n];
    for (int i = n; i > 0; --i) {
        int ind = 0;
        for (int j = 0; j < i; ++j) {
            ind = a[j] == i ? j : ind;
        }
        int b[i];
        for (int j = 0; j < i; ++j) {
            b[(i - 1 - ind + j) % i] = a[j];
        }
        for (int j = 0; j < i; ++j) {
            a[j] = b[j];
        }
        ans[i - 1] = i != 1 ? (ind + 1) % i : 0;
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
int main() {
    int tests;
    cin >> tests;
    forn(tt, tests) {
        solve();
    }
}
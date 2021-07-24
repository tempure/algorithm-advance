#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    double a, b;
    cin >> a >> b;
    double ans = (a - b) / 3 + b;
    printf("%f", ans);
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
}
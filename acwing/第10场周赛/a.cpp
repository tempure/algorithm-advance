#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll mod = 1e9 + 7;

void solve() {
    int a, b;
    int res ;
    cin >> a >> b;
    if (a % b == 0) res = 0;
    else {
        if (a < b) {
            res = b - a;
        }
        else {
            res = (a / b + 1) * b - a;
        }
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
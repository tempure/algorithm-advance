#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    string str;
    cin >> str;
    int n = (int)str.size();

    int res = 100;
    for (int i = 0; i < 1 << n; i++) {
        int x = 0;
        for (int j = 0; j < n; j++)
            if (i >> j & 1)
                x = x * 10 + str[j] - '0';
        int t = sqrt(x);
        if (x && t * t == x) res = min(res, n - (int)to_string(x).size());
    }
    if (res == 100) res = -1;
    cout << res << endl;
}


int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
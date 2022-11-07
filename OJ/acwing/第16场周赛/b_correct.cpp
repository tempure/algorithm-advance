#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
int s[N];
int n;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    if (s[n] % 3) {
        cout << 0 << endl;
        return;
    }

    ll res = 0;
    for (int i = 3, cnt = 0; i <= n; i ++ ) {
        if (s[i - 2] == s[n] / 3) cnt ++ ;
        if (s[n] - s[i - 1] == s[n] / 3) res += cnt;
    }
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}
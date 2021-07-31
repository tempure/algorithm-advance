#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll mod = 1e9 + 7;

/*
https://www.acwing.com/video/3338/
*/

const int N = 1e5 + 10;
ll s[N];
ll f[26][26];
char str[N];

void solve() {
    cin >> str;
    ll res = 0;
    for (int i = 0; str[i]; i++) {
        int t = str[i] - 'a';
        for (int j = 0; j < 26; j++) {
            f[j][t] += s[j];
            res = max(res, f[j][t]);
        }
        s[t]++;
        res = max(res , s[t]);
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
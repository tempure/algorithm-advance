#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
char s[N];
int ne[N];
bool st[N];
int n;

void solve() {
    cin >> s + 1;
    n = strlen(s + 1);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[i] != s[j + 1]) j = ne[j];
        if (s[i] == s[j + 1]) j++;
        ne[i] = j;
    }
    for (int i = 0; i <= n; i++) st[i] = false;
    for (int i = 1; i < n; i++) st[ne[i]] = true; //last pos ne[] rest to judge

    int res = 0;
    for (int i = ne[n]; i; i = ne[i])
        if (st[i]) {
            res = i;
            break;
        }
    if (!res) puts("not exist");
    else {
        s[res + 1] = 0;
        cout << s + 1 << endl;
    }
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
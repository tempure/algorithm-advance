#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int cntl = 0, cntr = 0;
    for (auto c : s) {
        if (c == '(') cntl++;
        else cntr++;
    }
    cout << min(cntl, cntr) * 2 << endl;
}

int main() {
    solve();
    return 0;
}

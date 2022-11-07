#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    string s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;
    string b[4] = {s1, s2, s3, s4};
    string a[4] = {"2B", "HR", "3B", "H"};
    bool flag = true;

    sort(a, a + 4);
    sort(b, b + 4);
    for (int i = 0; i < 4 ; i++) {
        if (a[i] != b[i]) {
            flag = false;
            break;
        }
    }

    if (flag) puts("Yes");
    else puts("No");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
}
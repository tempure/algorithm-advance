#include <bits/stdc++.h>
using namespace std;


//读不太懂这个题在干啥。。。。

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& u : a)
            cin >> u;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += (i + 1) * (n - i);
            if (a[i] == 0)
                ans += (i + 1) * (n - i);
        }
        cout << ans << '\n';
    }
}
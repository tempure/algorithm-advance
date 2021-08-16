#include <bits/stdc++.h>
using namespace std;

//题目可以说操作任意次。。草
//那就直接一直&就好了，反正&只会变小不会变大

void solve() {
    int n;
    cin >> n;
    int res = -1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        res &= x;
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
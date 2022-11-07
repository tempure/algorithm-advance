#include <bits/stdc++.h>
using namespace std;
int main() {
    map<int, pair<int, int>> mp;
    int a[3][3] = {};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
            mp[a[i][j]] = {i, j};
        }
    }
    int row[3] = {};
    int col[3] = {};
    int diago[3] = {};
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (mp.count(x)) {
            ++row[mp[x].first];
            ++col[mp[x].second];
            if (mp[x].first == mp[x].second)
                ++diago[0];
            if (mp[x].first + mp[x].second == 2)
                ++diago[1];
        }
    }
    bool ok = false;
    for (int i = 0; i < 3; i++) {
        ok |= row[i] == 3;
        ok |= col[i] == 3;
        ok |= diago[i] == 3;
    }
    cout << (ok ? "Yes" : "No");
}
//https://www.cnblogs.com/Kanoon/p/12940465.html
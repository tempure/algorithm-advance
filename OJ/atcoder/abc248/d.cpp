#include <bits/stdc++.h>
using namespace std;

//注意下标
//题目查询lr 1开始
// smallest element that is greater than or equal to L, and the smallest element that is strictly greater than R

int main() {
    int n;
    cin >> n;

    vector<vector<int>> idx(n + 1);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        idx[a].push_back(i);
    }

    int q;
    cin >> q;

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        cout << upper_bound(idx[x].begin(), idx[x].end(), r) - lower_bound(idx[x].begin(), idx[x].end(), l) << endl;
    }
}

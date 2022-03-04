#include <iostream>
#include <vector>
#include <map>
#include <atcoder/dsu>
using namespace std;
using namespace atcoder;

//https://atcoder.jp/contests/abc183/editorial/345
//这题意有些费解
//虽然一眼DSU，但是没看懂询问操作到底是啥。。。。

int main() {
    int n, q;
    cin >> n >> q;
    vector<map<int, int>> cnt(n);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        c--;
        cnt[i][c] = 1;
    }

    dsu d(n);
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        x--, y--;
        if (t == 1) {
            x = d.leader(x);
            y = d.leader(y);
            if (x != y) {
                int r = d.merge(x, y);
                if (r != x)swap(x, y);
                for (auto temp : cnt[y])cnt[x][temp.first] += temp.second;
            }
        } else {
            cout << cnt[d.leader(x)][y] << endl;
        }
    }
}
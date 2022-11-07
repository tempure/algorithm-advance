#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//N很小 直接暴力
//https://atcoder.jp/contests/abc183/editorial/342

int main () {
    int n, k;
    cin >> n >> k;
    vector<vector<int>>T(n, vector<int>(n));
    for (int i = 0; i < n; i++)for (int j = 0; j < n; j++) {
            cin >> T[i][j];
        }

    vector<int>index;
    for (int i = 0; i < n; i++)index.push_back(i);

    int ans = 0;
    do {
        int time = 0;
        for (int i = 0; i < n; i++)time += T[index[i]][index[(i + 1) % n]];
        if (time == k)ans++;
    } while (next_permutation(index.begin() + 1, index.end()));
    cout << ans;
}
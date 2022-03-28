#include <bits/stdc++.h>

using namespace std;

//https://atcoder.jp/contests/abc176/submissions/16120475
//https://atcoder.jp/contests/abc176/editorial/80
//独立看行和列 所有最大的行单独存 最大的列单独存 然后枚举

int n, m, k, ans;
map<int, int> mx, my;
map<int, vector<int>> xx, yy;
set<pair<int, int>> s;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    while (k--) {
        int ta, tb;
        scanf("%d%d", &ta, &tb);
        mx[ta]++;
        my[tb]++;
        s.insert({ta, tb});
    }
    for (auto& i : mx)
        xx[i.second].push_back(i.first); //最多的所有行
    for (auto& i : my)
        yy[i.second].push_back(i.first);//最多的所有列 不唯一 要枚举
    ans = xx.rbegin()->first + yy.rbegin()->first;
    for (int i : xx.rbegin()->second)
        for (int j : yy.rbegin()->second)
            if (!s.count({i, j})) { //存在一个该位没有target
                printf("%d\n", ans);
                return 0;
            }
    printf("%d\n", ans - 1); //所有最大的位置都有一个 target 只能减1了
}
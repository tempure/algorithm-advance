/*
来自论坛的帖子解法：https://projecteuler.net/action=redirect;post_id=13949
思路就是把面积分割为拐角4个正方形加上四个长方形，然后列出不等式，对于每个外边长，计算有多少个地砖环的宽度符合
外边长的范围：当内部小正方形为1个时，也就是极端情况，4 * x * x <= N => x <sqrt(N/4)

ans = 1572729
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6, c = N / 4, xm = sqrt(c);

void solve() {
    ll res = 0;
    for (int x = 1; x <= xm; x++) res += c / x - x;
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}

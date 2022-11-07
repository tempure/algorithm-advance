#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
前9个素数乘积已经大于2e9，所以最多只会用到9个素数
性质：一定是约数个数最大的数中最小的一个，因为最小的后面的大的数都不满足
证2：答案的质因子分解必然是连续素数，因为如果不连续，可以替换成前面空缺位置的素数，次数相同，约数个数不变，但是答案但是会变得更小
证2：答案的质因子分解次幂必然递减，如果递增，可以交换两个质因子的次幂，但是约数个数不变，答案变得更小
*/

int pm[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
int max_cnt, number;
int n;

void dfs(int u, int last, int p, int s) {
    if (s > max_cnt || (s == max_cnt && p < number)) {
        max_cnt = s;
        number = p;
    }
    if (u == 9) return;
    for (int i = 1; i <= last; i++) {
        if ((ll)p * pm[u] > n) break;
        p *= pm[u];
        dfs(u + 1, i, p, s * (i + 1));
    }
}

void solve() {
    cin >> n;
    dfs(0, 30, 1, 1);
    cout << number << endl;
}

int main() {
    solve();
    return 0;
}
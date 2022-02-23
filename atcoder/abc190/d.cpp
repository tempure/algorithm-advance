#include <iostream>
#include <cmath>
using namespace std;
using ll = int64_t;


//https://atcoder.jp/contests/abc190/editorial/692

/*
答案就是把2N分解为奇偶性不同的两个数的乘机的方案数量
先把2质因子全部除完，剩下都是奇的因子
此时就要把这些因子划分为2部分，一个奇的一个偶的
那么2的这些除掉的因子可以乘在任意一部分，所以就是2倍的剩余因子的数量
*/

int main() {
    ll N;
    cin >> N;
    while (N % 2 == 0) N /= 2;
    ll sq = sqrt(N), ans = 0;
    for (ll i = 1; i <= sq; i++) if (N % i == 0) ans += 2;
    if (sq * sq == N) ans--;
    cout << ans * 2 << endl;
}
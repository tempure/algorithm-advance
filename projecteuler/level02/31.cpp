#include<bits/stdc++.h>
using namespace std;

//完全背包求方案数?
//使用dp[i][j]表示利用最大面额为f[j]的纸币组成i有多少种方法。
// d[i][j] = dp[i][j] + sigma(k=[1,j])dp[i-f[j]][k]

int dp[210][10];
int coin[10] = {0, 1, 2, 5, 10, 20, 50, 100, 200, 1000};

int main() {
    dp[0][1] = 1;
    for (int i = 1; i <= 200; i++) {
        for (int j = 1; coin[j] <= i; j++) {
            for (int k = 1; k <= j; k++) {
                dp[i][j] += dp[i - coin[j]][k];
            }
        }
    }
    for (int i = 1; i <= 10; i++) dp[200][0] += dp[200][i];
    cout << dp[200][0] << endl;
    return 0;
}